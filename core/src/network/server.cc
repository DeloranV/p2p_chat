//
// Created by rolandpwrrt on 7.10.2025.
//
#include "network/server.h"
#include "crypto/cert_gen.h"
#include <functional>
// TODO IMPLEMENTATION DETAILS FOR THE LIB INSIDE OF ::detail NAMESPACE
// TODO WHETHER WE WANT TO HAVE ENCRYPTION OR NOT
// TODO MAKE USER PASS A HANDLER WHICH RETURN A bool TO EVAULATE WHETHER A CONNECTION SHOULD HAPPEN OR NOT
namespace networking {
  Server::Server(boost::asio::io_context &io_context)
    : io_context_(io_context),
      ctx(ssl::context::sslv23),
      socket_(io_context),
      acceptor_(tcp::acceptor(io_context, tcp::endpoint(tcp::v4(), 33333))) // TODO MOVE PORT TO GLOBAL CONFIG
  {
  }

  Server::~Server() {
    acceptor_.close();
  }

  void Server::configure_tls() {
    ctx.set_options(
      ssl::context::default_workarounds
      | ssl::context::no_sslv2
      | ssl::context::single_dh_use);
    ctx.use_certificate_chain_file("../../ssl_test_keys_backup/server.crt");
    ctx.use_private_key_file("../../ssl_test_keys_backup/server.key", ssl::context::pem);
  }

  void Server::handle_accept(const boost::system::error_code &error, std::function<void(ssl_socket)> callback) {
    if (!error) {
      ssl_socket s_socket(std::move(socket_), ctx);
      s_socket.handshake(ssl::stream_base::server);
      callback(std::move(s_socket));
      // TODO maybe we should post ? dunno if await_connection below should be called immediately
      //manager.start_session(std::move(s_socket), adapter);
    }
    await_connection(callback);
  }

  void Server::await_connection(std::function<void(ssl_socket)> callback) {
    acceptor_.async_accept(socket_,
                           boost::bind(&Server::handle_accept, this, boost::placeholders::_1, callback));
    // std::move SINCE WE NEED TO TRANSFER OWNERSHIP OF THE SOCKET TO THE SESSION OBJECT
    //return std::make_shared<session::chat_session>(io_context_, std::move(s_socket), adapter);
  }
};
