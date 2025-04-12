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

#include "discord_serialization.h"
#include "discord_rpc.h"

using namespace Qt::Literals::StringLiterals;

namespace discord_rpc {

template<typename T>
void NumberToString(char *dest, T number) {

  if (!number) {
    *dest++ = '0';
    *dest++ = 0;
    return;
  }
  if (number < 0) {
    *dest++ = '-';
    number = -number;
  }
  char temp[32];
  int place = 0;
  while (number) {
    auto digit = number % 10;
    number = number / 10;
    temp[place++] = '0' + static_cast<char>(digit);
  }
  for (--place; place >= 0; --place) {
    *dest++ = temp[place];
  }
  *dest = 0;

}

void WriteOptionalString(QJsonObject &json_object, const QString &key, const QString &value);
void WriteOptionalString(QJsonObject &json_object, const QString &key, const QString &value) {

  if (!value.isEmpty()) {
    json_object[key] = value;
  }

}

static QString JsonWriteNonce(const int nonce) {

  char nonce_buffer[32]{};
  NumberToString(nonce_buffer, nonce);

  return QString::fromLatin1(nonce_buffer);

}

size_t JsonWriteRichPresenceObj(char *dest, const size_t maxLen, const int nonce, const int pid, const DiscordRichPresence &presence) {

  QJsonObject json_object;

  json_object["nonce"_L1] = JsonWriteNonce(nonce);
  json_object["cmd"_L1] = "SET_ACTIVITY"_L1;

  QJsonObject args;
  args["pid"_L1] = pid;

  QJsonObject activity;

  if (presence.type >= 0 && presence.type <= 5) {
    activity["type"_L1] = presence.type;
  }

  activity["state"_L1] = presence.state;
  activity["details"_L1] = presence.details;

  if (presence.startTimestamp != 0 || presence.endTimestamp != 0) {
    QJsonObject timestamps;
    if (presence.startTimestamp != 0) {
      timestamps["start"_L1] = presence.startTimestamp;
    }
    if (presence.endTimestamp != 0) {
      timestamps["end"_L1] = presence.endTimestamp;
    }
    activity["timestamps"_L1] = timestamps;
  }

  if (!presence.largeImageKey.isEmpty() || !presence.largeImageText.isEmpty() || !presence.smallImageKey.isEmpty() || !presence.smallImageText.isEmpty()) {
    QJsonObject assets;
    WriteOptionalString(assets, "large_image"_L1, presence.largeImageKey);
    WriteOptionalString(assets, "large_text"_L1, presence.largeImageText);
    WriteOptionalString(assets, "small_image"_L1, presence.smallImageKey);
    WriteOptionalString(assets, "small_text"_L1, presence.smallImageText);
    activity["assets"_L1] = assets;
  }

  activity["instance"_L1] = presence.instance != 0;
  args["activity"_L1] = activity;
  json_object["args"_L1] = args;

  QJsonDocument json_document(json_object);
  QByteArray data = json_document.toJson(QJsonDocument::Compact);
  strncpy(dest, data.constData(), maxLen);

  return data.length();

}

size_t JsonWriteHandshakeObj(char *dest, const size_t maxLen, const int version, const QString &applicationId) {

  QJsonObject json_object;
  json_object["v"_L1] = version;
  json_object["client_id"_L1] = applicationId;
  const QJsonDocument json_document(json_object);
  const QByteArray data = json_document.toJson(QJsonDocument::Compact);
  strncpy(dest, data.constData(), maxLen);

  return data.length();

}

size_t JsonWriteSubscribeCommand(char *dest, const size_t maxLen, const int nonce, const char *evtName) {

  QJsonObject json_object;
  json_object["nonce"_L1] = JsonWriteNonce(nonce);
  json_object["cmd"_L1] = "SUBSCRIBE"_L1;
  json_object["evt"_L1] = QLatin1String(evtName);
  const QJsonDocument json_document(json_object);
  const QByteArray data = json_document.toJson(QJsonDocument::Compact);
  strncpy(dest, data.constData(), maxLen);

  return data.length();

}

size_t JsonWriteUnsubscribeCommand(char *dest, const size_t maxLen, const int nonce, const char *evtName) {

  QJsonObject json_object;
  json_object["nonce"_L1] = JsonWriteNonce(nonce);
  json_object["cmd"_L1] = "UNSUBSCRIBE"_L1;
  json_object["evt"_L1] = QLatin1String(evtName);
  const QJsonDocument json_document(json_object);
  const QByteArray data = json_document.toJson(QJsonDocument::Compact);
  strncpy(dest, data.constData(), maxLen);

  return data.length();

}

size_t JsonWriteJoinReply(char *dest, size_t maxLen, const char *userId, const int reply, const int nonce) {

  QJsonObject json_object;
  json_object["nonce"_L1] = JsonWriteNonce(nonce);
  json_object["cmd"_L1] = reply == DISCORD_REPLY_YES ? "SEND_ACTIVITY_JOIN_INVITE"_L1 : "CLOSE_ACTIVITY_JOIN_REQUEST"_L1;
  QJsonObject args;
  args["user_id"_L1] = QLatin1String(userId);
  json_object["args"_L1] = args;
  const QJsonDocument json_document(json_object);
  const QByteArray data = json_document.toJson(QJsonDocument::Compact);
  strncpy(dest, data.constData(), maxLen);

  return data.length();

}

}  // namespace discord_rpc
