#ifndef P2P_CHAT_CORE_LIB_UTIL_UTIL_H_
#define P2P_CHAT_CORE_LIB_UTIL_UTIL_H_

#include <boost/asio/ssl.hpp>
#include <boost/date_time.hpp>
#include <string>

#include "message.pb.h"

namespace chat_lib::util {

enum class ChatError { kOk, kRemoteHostDisconnect, kUnknownError };

inline ChatError TranslateError(const boost::system::error_code& ec) {
  namespace ssl = boost::asio::ssl;

  if (!ec) return ChatError::kOk;
  if (ec == ssl::error::stream_truncated || ec == boost::asio::error::eof ||
      ec == boost::asio::error::connection_reset ||
      ec == boost::asio::error::broken_pipe)
    return ChatError::kRemoteHostDisconnect;
  return ChatError::kUnknownError;
}

inline messages::ChatMessage DeserializeMessage(const std::string& payload) {
  messages::ChatMessage deserialized;
  deserialized.ParseFromString(payload);
  return deserialized;
}

inline std::string SerializeMessage(const std::string& local_ip,
                                     const std::string& msg_contents) {
  messages::ChatMessage msg;
  auto timestamp = boost::posix_time::to_simple_string(
      boost::posix_time::second_clock::local_time().time_of_day());
  msg.set_timestamp(timestamp);
  msg.set_msg_contents(msg_contents);
  msg.set_sender_ip(local_ip);
  return msg.SerializeAsString();
}

inline std::string MsgAsString(const messages::ChatMessage& msg) {
  return msg.timestamp() + " " + msg.sender_ip() + ": " + msg.msg_contents();
}
// (TODO) Formatted message should be its own type
inline std::string SentMsg(const std::string& local_ip,
                                const std::string& msg_contents) {
  return boost::posix_time::to_simple_string(
             boost::posix_time::second_clock::local_time().time_of_day()) +
         " " + local_ip + "(you): " + msg_contents;
}
}  // namespace chat_lib::util

#endif  // P2P_CHAT_CORE_LIB_UTIL_UTIL_H_