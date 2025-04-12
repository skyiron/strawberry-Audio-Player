/*
 * Copyright 2017 Discord, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

#include "discord_rpc_connection.h"
#include "discord_serialization.h"

using namespace Qt::Literals::StringLiterals;

namespace discord_rpc {

static const int RpcVersion = 1;
static RpcConnection Instance;

RpcConnection *RpcConnection::Create(const QString &applicationId) {

  Instance.connection = BaseConnection::Create();
  Instance.appId = applicationId;
  return &Instance;

}

void RpcConnection::Destroy(RpcConnection *&c) {

  c->Close();
  BaseConnection::Destroy(c->connection);
  c = nullptr;

}

void RpcConnection::Open() {

  if (state == State::Connected) {
    return;
  }

  if (state == State::Disconnected && !connection->Open()) {
    return;
  }

  if (state == State::SentHandshake) {
    QJsonDocument json_document;
    if (Read(json_document)) {
      const QJsonObject json_object = json_document.object();
      const QString cmd = json_object["cmd"_L1].toString();
      const QString evt = json_object["evt"_L1].toString();
      if (cmd == "DISPATCH"_L1 && evt == "READY"_L1) {
        state = State::Connected;
        if (onConnect) {
          onConnect(json_document);
        }
      }
    }
  }
  else {
    sendFrame.opcode = Opcode::Handshake;
    sendFrame.length = static_cast<uint32_t>(JsonWriteHandshakeObj(sendFrame.message, sizeof(sendFrame.message), RpcVersion, appId));

    if (connection->Write(&sendFrame, sizeof(MessageFrameHeader) + sendFrame.length)) {
      state = State::SentHandshake;
    }
    else {
      Close();
    }
  }

}

void RpcConnection::Close() {

  if (onDisconnect && (state == State::Connected || state == State::SentHandshake)) {
    onDisconnect(lastErrorCode, lastErrorMessage);
  }
  connection->Close();
  state = State::Disconnected;

}

bool RpcConnection::Write(const void *data, size_t length) {

  sendFrame.opcode = Opcode::Frame;
  memcpy(sendFrame.message, data, length);
  sendFrame.length = static_cast<uint32_t>(length);
  if (!connection->Write(&sendFrame, sizeof(MessageFrameHeader) + length)) {
    Close();
    return false;
  }

  return true;

}

bool RpcConnection::Read(QJsonDocument &message) {

  if (state != State::Connected && state != State::SentHandshake) {
    return false;
  }
  MessageFrame readFrame{};
  for (;;) {
    bool didRead = connection->Read(&readFrame, sizeof(MessageFrameHeader));
    if (!didRead) {
      if (!connection->isOpen) {
        lastErrorCode = static_cast<int>(ErrorCode::PipeClosed);
        lastErrorMessage = "Pipe closed"_L1;
        Close();
      }
      return false;
    }

    if (readFrame.length > 0) {
      didRead = connection->Read(readFrame.message, readFrame.length);
      if (!didRead) {
        lastErrorCode = static_cast<int>(ErrorCode::ReadCorrupt);
        lastErrorMessage = "Partial data in frame"_L1;
        Close();
        return false;
      }
      readFrame.message[readFrame.length] = 0;
    }

    switch (readFrame.opcode) {
      case Opcode::Close: {
        message = QJsonDocument::fromJson(readFrame.message);
        lastErrorCode = message["code"_L1].toInt();
        lastErrorMessage = message["message"_L1].toString();
        Close();
        return false;
      }
      case Opcode::Frame:
        message = QJsonDocument::fromJson(readFrame.message);
        return true;
      case Opcode::Ping:
        readFrame.opcode = Opcode::Pong;
        if (!connection->Write(&readFrame, sizeof(MessageFrameHeader) + readFrame.length)) {
          Close();
        }
        break;
      case Opcode::Pong:
        break;
      case Opcode::Handshake:
      default:
        // something bad happened
        lastErrorCode = static_cast<int>(ErrorCode::ReadCorrupt);
        lastErrorMessage = "Bad ipc frame"_L1;
        Close();
        return false;
    }
  }

}

}  // namespace discord_rpc
