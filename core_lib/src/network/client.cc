#include "network/client.h"

#include <boost/asio.hpp>

namespace chat_lib::networking {

using ssl::verify_context;

Client::Client(boost::asio::io_context &io_context)
    : io_context_(io_context),
      ctx_(ssl::context::sslv23),
      resolver_(io_context) {}

ssl_socket Client::try_connect(const std::string &target_ip) {
  ssl_socket socket(io_context_, ctx_);
  socket.set_verify_mode(ssl::verify_peer | ssl::verify_fail_if_no_peer_cert);
  socket.set_verify_callback(
      [](bool /*preverified*/,
         verify_context & /*ctx*/) {  // (TODO #1) Implement cert verification
        return true;
      });
  auto endpoints = resolver_.resolve(target_ip, "33333");
  boost::asio::connect(socket.lowest_layer(), endpoints);
  socket.handshake(ssl::stream_base::client);
  return std::move(socket);
}

}  // namespace chat_lib::networking

/*
=========================================================================
LEARNING NOTES & IMPLEMENTATION DETAILS (For Future Reference)
=========================================================================

  [SSL Handshake Logic]
  There are multiple verification modes possible, but here the verification
  callback was implemented only on the client, since the planned certificate
  and public key flow is Server --> Client. Upon receiving, the
  client checks the server's certificate and verifies it using our given
  callback. After successful verification, the client encrypts a generated
  symmetric session key with the public key of the server. Then it gets sent
  back to the server, which decrypts it with its own private key and a session
  is established. From that point on, both are using the agreed upon session
  key for encrypting the messages.

  - Observation: The handshake process can be observed through Wireshark. If the
  client verification callback returns false, then an "unknown CA" packet gets
  sent to the server and the session terminates.
  - Reference: https://docs.openssl.org/3.0/man3/SSL_CTX_set_verify/

  [Return Value Strategy]
  The try_connect function initially returned the moved socket by rvalue ref.
  That posed a problem, since the object was local to the function and got
  destroyed as soon as it ended, leaving the caller with a dangling reference
  to invalid memory. Returning by value allows the compiler itself to use move
  semantics or RVO.
  REMEMBER - A FUNCTION FIRST EXITS AND CLEANS UP ITS STACK AND RETURNS THE
  VALUE AFTERWARD - NOT SIMULTANEOUSLY
*/