#ifndef CHAT_APP_UTIL_H
#define CHAT_APP_UTIL_H

#include <boost/asio/ssl.hpp>
#include <boost/date_time.hpp>
#include <string>

#include "message.pb.h"

namespace chat_lib {

namespace util {

enum Mode { SERVER, CLIENT, EXIT };
enum ClientChoice { TARGET_IP, HOST_LIST };
enum ListeningMode { PASSIVE, ACTIVE };

enum class ChatError { OK, REMOTE_HOST_DISCONNECT, UNKNOWN_ERROR };

static ChatError translate_error(const boost::system::error_code& ec) {
  namespace ssl = boost::asio::ssl;

  if (!ec) return ChatError::OK;
  if (ec == ssl::error::stream_truncated)
    return ChatError::REMOTE_HOST_DISCONNECT;
  return ChatError::UNKNOWN_ERROR;
}

static messages::ChatMessage deserialize_message(const std::string& payload) {
  messages::ChatMessage deserialized;
  deserialized.ParseFromString(payload);
  return deserialized;
}

static std::string serialize_message(std::string local_ip,
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

static std::string sent_message(const std::string& local_ip,
                                const std::string& msg_contents) {
  return boost::posix_time::to_simple_string(
             boost::posix_time::second_clock::local_time().time_of_day()) +
         " " + local_ip + "(you): " + msg_contents;
}

}  // namespace util

}  // namespace chat_lib

#endif  // CHAT_APP_UTIL_H