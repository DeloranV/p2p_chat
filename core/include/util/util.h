//
// Created by rolandpwrrt on 7.10.2025.
//

#ifndef CHAT_APP_UTIL_H
#define CHAT_APP_UTIL_H

#include <string>
#include <boost/date_time.hpp>

namespace util {
  enum Mode { SERVER, CLIENT, EXIT };
  enum ClientChoice { TARGET_IP, HOST_LIST };
  enum ListeningMode {PASSIVE, ACTIVE};

  // TODO PROTOBUF SERIALIZATION
  static std::string deserialize_message(std::string& payload) {
    auto first_delim = payload.find('|');
    auto second_delim = first_delim + payload.substr(first_delim + 1).find('|') + 1;
    std::string timestamp = payload.substr(0, first_delim);
    std::string content = payload.substr(first_delim + 1, second_delim - first_delim - 1);
    std::string ip_address = payload.substr(second_delim + 1);
    std::string deserialized = timestamp + " " + ip_address + ": " + content;
    return deserialized;
  }

  static std::string serialize_message(const std::string& local_ip, const std::string& msg_contents) {
    return boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time().time_of_day()) +
      "|" + msg_contents + "|" + local_ip;
  }

  static std::string sent_message(const std::string& local_ip, const std::string& msg_contents) {
    return boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time().time_of_day()) +
      " " + local_ip + "(you): " + msg_contents;
  }

}

#endif //CHAT_APP_UTIL_H