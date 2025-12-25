#ifndef CHAT_APP_UTIL_H
#define CHAT_APP_UTIL_H

#include <boost/asio/ssl.hpp>
#include <boost/date_time.hpp>
#include <string>

#include "message.pb.h"

namespace chat_lib::util {

enum class ChatError { OK, REMOTE_HOST_DISCONNECT, UNKNOWN_ERROR };

inline ChatError translate_error(const boost::system::error_code& ec) {
  namespace ssl = boost::asio::ssl;

  if (!ec) return ChatError::OK;
  if (ec == ssl::error::stream_truncated || ec == boost::asio::error::eof ||
      ec == boost::asio::error::connection_reset ||
      ec == boost::asio::error::broken_pipe)
    return ChatError::REMOTE_HOST_DISCONNECT;
  return ChatError::UNKNOWN_ERROR;
}

inline messages::ChatMessage deserialize_message(const std::string& payload) {
  messages::ChatMessage deserialized;
  deserialized.ParseFromString(payload);
  return deserialized;
}

inline std::string serialize_message(const std::string& local_ip,
                                     const std::string& msg_contents) {
  messages::ChatMessage msg;
  auto timestamp = boost::posix_time::to_simple_string(
      boost::posix_time::second_clock::local_time().time_of_day());
  msg.set_timestamp(timestamp);
  msg.set_msg_contents(msg_contents);
  msg.set_sender_ip(local_ip);
  return msg.SerializeAsString();
}

inline std::string msg_as_string(const messages::ChatMessage& msg) {
  return msg.timestamp() + " " + msg.sender_ip() + ": " + msg.msg_contents();
}
// (TODO) Formatted message should be its own type
inline std::string sent_message(const std::string& local_ip,
                                const std::string& msg_contents) {
  return boost::posix_time::to_simple_string(
             boost::posix_time::second_clock::local_time().time_of_day()) +
         " " + local_ip + "(you): " + msg_contents;
}
}  // namespace chat_lib::util

#endif  // CHAT_APP_UTIL_H