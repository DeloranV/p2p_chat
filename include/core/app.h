//
// Created by rolandpwrrt on 7.10.2025.
//

#ifndef CHAT_APP_APP_H
#define CHAT_APP_APP_H

#include <memory>
#include <boost/asio.hpp>
#include "cli/cli.h"
#include "network/network.h"
#include "util/util.h"

class CLI_application {
public:
  CLI_application(boost::asio::io_context& io_context);
  void run();
  void start_client(std::string target_ip);
  void start_server();

private:
  boost::asio::io_context& io_context_;
  std::shared_ptr<CLI::CLI_Manager> cli_manager_;
  std::shared_ptr<networking::Server> server_;
  std::shared_ptr<networking::Client> client_;
  std::shared_ptr<session::chat_session> session_;
};

#endif //CHAT_APP_APP_H