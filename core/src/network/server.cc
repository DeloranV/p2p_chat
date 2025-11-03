#include "network/server.h"

#include <functional>

#include "crypto/cert_gen.h"
// TODO IMPLEMENTATION DETAILS FOR THE LIB INSIDE OF ::detail NAMESPACE
// TODO MAKE USER PASS A HANDLER WHICH RETURN A bool TO EVAULATE WHETHER A
// CONNECTION SHOULD HAPPEN OR NOT

namespace chat_lib {

namespace networking {

Server::Server(boost::asio::io_context& io_context)
    : io_context_(io_context),
      ctx(ssl::context::sslv23),
      socket_(io_context),
      acceptor_(tcp::acceptor(
          io_context,
          tcp::endpoint(tcp::v4(), 33333)))  // TODO MOVE PORT TO GLOBAL CONFIG
{
  crypto::create_private_key();
  configure_tls();
}

Server::~Server() { acceptor_.close(); }

void Server::configure_tls() {
  ctx.set_options(ssl::context::default_workarounds | ssl::context::no_sslv2 |
                  ssl::context::single_dh_use);
  ctx.use_certificate_chain_file("cert.pem");
  ctx.use_private_key_file("key.pem", ssl::context::pem);
}

void Server::handle_accept(const boost::system::error_code& error,
                           const acceptor_handler_t& callback) {
  if (!error) {
    ssl_socket s_socket(std::move(socket_), ctx);
    s_socket.handshake(ssl::stream_base::server);
    callback(std::move(s_socket));
    // TODO maybe we should post ? dunno if await_connection below should be
    // called immediately
    // manager.start_session(std::move(s_socket), adapter);
  }
  await_connection(callback);
}

void Server::await_connection(const acceptor_handler_t& callback) {
  acceptor_.async_accept(socket_, std::bind(&Server::handle_accept, this,
                                            std::placeholders::_1, callback));
}
};  // namespace networking

}  // namespace chat_lib
