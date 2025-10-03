//
// Created by rolandpwrrt on 7.10.2025.
//

#include "core/app.h"

  CLI_application::CLI_application(boost::asio::io_context& io_context, utilities::Mode programMode)
    : cli_manager_(std::make_shared<CLI::CLI_Manager>()), io_context_(io_context)
  {
    CLI::display_welcome();
    if (programMode == utilities::Mode::SERVER) {
      server_ = std::make_shared<networking::p2p_server>(io_context);
    }
    else {
      client_ = std::make_shared<networking::p2p_client>(io_context);
    }
  }

  void CLI_application::run_client(std::string target_ip) {
    session_ = client_->create_session(target_ip);
    session_->listen_msg();

    cli_manager_->await_input(std::bind(&session::chat_session::send_msg, session_, std::placeholders::_1));
    io_context_.run();
  }

  void CLI_application::run_server() {
    session_ = server_->create_session();
    session_->listen_msg();

    cli_manager_->await_input(std::bind(&session::chat_session::send_msg, session_, std::placeholders::_1));
    io_context_.run();
  }

