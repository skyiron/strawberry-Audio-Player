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

#ifndef DISCORD_SERIALIZATION_H
#define DISCORD_SERIALIZATION_H

#include <cstddef>
#include <QString>

namespace discord_rpc {

size_t JsonWriteHandshakeObj(char *dest, size_t maxLen, int version, const QString &applicationId);
class DiscordRichPresence;
size_t JsonWriteRichPresenceObj(char *dest, const size_t maxLen, const int nonce, const int pid, const DiscordRichPresence &presence);
size_t JsonWriteSubscribeCommand(char *dest, size_t maxLen, int nonce, const char *evtName);
size_t JsonWriteUnsubscribeCommand(char *dest, size_t maxLen, int nonce, const char *evtName);
size_t JsonWriteJoinReply(char *dest, size_t maxLen, const char *userId, int reply, int nonce);

}  // namespace discord_rpc

#endif  // DISCORD_SERIALIZATION_H
