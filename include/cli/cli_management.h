//
// Created by rolandpwrrt on 7.10.2025.
//

#ifndef CHAT_APP_CLI_MANAGER_H
#define CHAT_APP_CLI_MANAGER_H

#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include <iostream>

namespace CLI {
  static void display_welcome() {
    std::cout << "\x1b[1;35;1m" << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++" <<
         " P2P CHAT APP - v0.5 " << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << "\x1b[0m" <<
          "\x1b[1;36;3m" << "\nToday is: " << "\x1b[0m" << "\x1b[1;31;4m" <<
         boost::gregorian::day_clock::local_day() << "\x1b[0m" << std::endl;
  }

  static void overwrite_prompt_character() {
    std::cout << "\x1b[1D" << std::flush; // MOVE CURSOR TO THE LEFT TO OVERWRITE THE ">" CHARACTER
  }

  static void display_received_msg(std::string& deserialized_msg) {
    overwrite_prompt_character();
    std::cout << deserialized_msg << std::endl;
    std::cout << ">" << std::flush;
  }

  static void display_sent_msg(std::string your_ip, std::string msg) {
    overwrite_prompt_character();
    std::cout << boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time().time_of_day()) <<
      ' ' << your_ip << "\x1b[1;34;1m" << "(you): " << "\x1b[0m" << msg << std::endl;
    std::cout << ">" << std::flush;
  }

  static void get_user_input(std::string& out) {
    std::cout << ">" << std::flush;
    std::getline(std::cin, out);
    std::cout << "\x1b[1A" << "\x1b[2K" << std::flush;  // CLEARS THE ECHOED LINE
  }
  static void display_conn_accepted(const std::string& accepted_ip) {
    std::cout << "\x1b[1;42mCONNECTION ACCEPTED FROM " <<
        accepted_ip << "\x1b[0m" << std::endl;

  }
  class CLI_Manager {
  public:
    CLI_Manager() = default;
    void await_input(std::function<void(std::string)> callback);

  private:
    boost::thread input_thread_;
  };
}

#endif //CHAT_APP_CLI_MANAGER_H