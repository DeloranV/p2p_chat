//
// Created by rolandpwrrt on 7.10.2025.
//
#include "network/server.h"

#include <cli/cli_management.h>

namespace networking {
  Server::Server(boost::asio::io_context& io_context)
      : io_context_(io_context),
        ctx(ssl::context::sslv23),
        socket_(io_context),
        acceptor_(tcp::acceptor(io_context, tcp::endpoint(tcp::v4(), std::stoi(CLI::obtain_port()))))
  {
    ctx.set_options(
      ssl::context::default_workarounds
      | ssl::context::no_sslv2
      | ssl::context::single_dh_use);
    //ctx.set_password_callback();  TODO ?
    ctx.use_certificate_chain_file("../ssl_test_keys/server.crt");
    ctx.use_private_key_file("../ssl_test_keys/server.key", ssl::context::pem);
    ctx.use_tmp_dh_file("../ssl_test_keys/dh2048.pem");
  }

    Server::~Server() {
      acceptor_.cancel();
      acceptor_.close();
    }

    std::shared_ptr<session::chat_session> Server::create_session() {
      CLI::server_listen();
      acceptor_.accept(socket_);
      ssl_socket s_socket (std::move(socket_), ctx);
      s_socket.handshake(ssl::stream_base::server);
      // std::move SINCE WE NEED TO TRANSFER OWNERSHIP OF THE SOCKET TO THE SESSION OBJECT
      return std::make_shared<session::chat_session>(io_context_, std::move(s_socket));
    }
  };