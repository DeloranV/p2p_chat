#include "network/server.h"

#include "crypto/cert_gen.h"

namespace chat_lib::networking {

Server::Server(boost::asio::io_context& io_context)
    : io_context_(io_context),
      ctx(ssl::context::sslv23),
      acceptor_(tcp::acceptor(
          io_context,
          tcp::endpoint(tcp::v4(), 33333)))  // (TODO #2) Move port to global config
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

void Server::await_connection(const acceptor_handler_t& callback) {
  auto s_socket = std::make_shared<ssl_socket>(io_context_, ctx);

  acceptor_.async_accept(
      s_socket->lowest_layer(),
      [shared_this = shared_from_this(), s_socket,
       callback](const boost::system::error_code& error) {
        if (error == boost::asio::error::operation_aborted) return;
        if (!error) {
          s_socket->async_handshake(
              ssl::stream_base::server,
              [callback, s_socket](const boost::system::error_code& error) {
                if (!error) callback(std::move(*s_socket));
              });
        }
        shared_this->await_connection(callback);
      });
}
};  // namespace chat_lib::networking

/*
=========================================================================
LEARNING NOTES & IMPLEMENTATION DETAILS (For Future Reference)
=========================================================================

  [Asynchronous operation]
  Using async variants of accept/handshake makes sure that the server runs in
  a non-blocking manner, where it is able to accept connections/perform
  handshakes and simultaneously listen or accept other incoming connections.
  This is done thanks to async methods posting the pending operations to the
  io_context queue (which get picked up by worker threads), and immediately
  returning and calling the passed handlers upon a connection
  arriving/finishing a handshake.

  [shared_from_this]
  A shared *this is used in the async_accept callback to ensure that the
  Server instance will be alive for as long as it awaits connections. However,
  now whenever a Server is created it needs to be contained inside a shared_ptr
  to support the shared ownership semantics.

*/