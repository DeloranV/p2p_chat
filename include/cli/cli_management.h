//
// Created by rolandpwrrt on 7.10.2025.
//

#ifndef CHAT_APP_CLI_MANAGER_H
#define CHAT_APP_CLI_MANAGER_H

#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include <iostream>
#include <util/util.h>
#include <termios.h>
#include "core/session.h"

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

  static void disable_echo() {
    struct termios term;
    tcgetattr(fileno(stdin), &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(fileno(stdin), 0, &term);
  }

  static void enable_echo() {
    struct termios term;
    tcgetattr(fileno(stdin), &term);
    term.c_lflag |= ECHO;
    tcsetattr(fileno(stdin), 0, &term);
  }

  // TODO GET TERMINAL WIDTH AND CALCULATE WHEN TEXT WRAPS TO GET NUMBER OF LOGICAL LINES PRINTED
  static void clear_console(int lines_printed) {
    for (int i = 0; i < lines_printed; ++i) {
      std::cout << "\x1b[2K" << "\x1b[1A" << std::flush;
    }
    std::cout << "\r" << std::flush;
  }

  static void server_listen() {
    std::cout << "Listening for connections..." << std::endl; // TODO SOME TEXT FORMATTING
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

  static util::Mode mode_menu() {
    display_welcome();
    while (true) {
      std::string choice;
      std::cout << "Choose mode:\n1)Server\n2)Client\n3)Exit" << std::endl;
      std::getline(std::cin, choice);
      clear_console(4);
      // TODO ASSIGN THESE VALUES TO ENUM AND RETURN ENUM VALUE - MORE CLEAN
      if (choice == "1") return util::SERVER;
      if (choice == "2") return util::CLIENT;
      if (choice == "3") return util::EXIT;
    }
  }

  static std::string target_ip_host_mode() {
    std::string target_ip;
    std::cout << "Input IP of the target you want to connect to:" << std::endl;
    std::getline(std::cin, target_ip);
    clear_console(2);
    return target_ip;
  }

  static std::string obtain_port() {
    std::cout << "Which port to open/connect to?" << std::endl;
    std::string port;
    std::getline(std::cin, port);
    clear_console(2);
    return port;
  }

  // TODO IMPLEMENT KNOWN HOSTS LIST - WILL TRANSLATE A SAVED HOST TO A TARGET IP AND RETURN IT TOO
  // TODO DISABLE CONSOLE ECHO FOR ALL MENUS ?
  // MAKE A GENERIC FUNCTION TAKING A TEMPLATE INSTEAD OF THESE TWO
  static std::string obtain_target_ip() {
    while (true) {
      std::string choice;
      std::cout << "How do you want to connect ?:\n1)Input target IP\n2)Select from saved hosts" << std::endl;
      std::getline(std::cin, choice);
      clear_console(4);
      if (choice == "1") return target_ip_host_mode();
      //if (choice == "2") return util::HOST_LIST;
    }
  }

  class CLI_Manager {
  public:
    CLI_Manager() = default;
    ~CLI_Manager();
    void await_input(std::function<void(std::string)> callback);

  private:
    boost::thread input_thread_;
  };
}

#endif //CHAT_APP_CLI_MANAGER_H