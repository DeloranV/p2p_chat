//
// Created by rolandpwrrt on 7.10.2025.
//

#include "core/app.h"

  CLI_application::CLI_application(boost::asio::io_context& io_context)
    : cli_manager_(std::make_shared<CLI::CLI_Manager>()), io_context_(io_context)
  {}

  void CLI_application::run() {
    while (true) {
      auto programMode = CLI::mode_menu();
      if (programMode == util::Mode::EXIT) break;
      if (programMode == util::Mode::SERVER) {
        server_ = std::make_shared<networking::Server>(io_context_);
        start_server();
        server_.reset();
      }
      else {
        auto target_ip = CLI::obtain_target_ip();
        client_ = std::make_shared<networking::Client>(io_context_);
        start_client(target_ip);
        client_.reset();
      }
      cli_manager_.reset(new CLI::CLI_Manager());
      session_.reset();
      io_context_.restart();  // AFTER IO_CONTEXT HAS BEEN STOPPED WE NEED TO RESTART IT
    }
  }

  void CLI_application::start_client(std::string target_ip) {
    session_ = client_->create_session(target_ip);
    session_->listen_msg();

    cli_manager_->await_input(
      std::bind(&session::chat_session::send_msg, session_, std::placeholders::_1));
    io_context_.run();
  }

  void CLI_application::start_server() {
    session_ = server_->create_session();
    session_->listen_msg();

    cli_manager_->await_input(
      std::bind(&session::chat_session::send_msg, session_, std::placeholders::_1));
    io_context_.run();
  }

