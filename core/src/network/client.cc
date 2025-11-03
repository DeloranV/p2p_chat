#include "network/client.h"

#include <boost/asio.hpp>
#include <iostream>

// SET VERIFY CALLBACK ONLY ON PEER SINCE THE PUBLIC KEY AND CERT ONLY GETS SENT
// SERVER -> CLIENT THEN CLIENT CHECKS THE SERVER CERTIFICATE AND VERIFIES THE
// SERVER (WITH OUR CALLBACK) THEN ENCRYPTS THE SESSION KEY WITH THE PUBLIC KEY
// SENDS TO SERVER AND SERVERS DECRYPTS WITH ITS PRIVATE KEY AND THEN THE
// SESSION USES THE AGREED UPON KEY
// https://docs.openssl.org/3.0/man3/SSL_CTX_set_verify/#notes - CHECK
// SSL_VERIFY_PEER IN CLIENT MODE CLIENT MODE SINCE WE CALL THE HANDSHAKE AS A
// CLIENT IF IT RETURN false AND WE INSPECT WITH WIRESHARK THEN WE CAN SEE THAT
// THE CLIENT SENDS AN unknown CA ALERT AND TERMINATES THE SESSION

using ssl::verify_context;

namespace chat_lib {

namespace networking {

Client::Client(boost::asio::io_context &io_context)
    : io_context_(io_context),
      ctx_(ssl::context::sslv23),
      resolver_(io_context) {}

// WHY RETURN BY RVALUE REF WON'T WORK ?
ssl_socket Client::try_connect(const std::string &target_ip) {
  ssl_socket socket(io_context_, ctx_);
  socket.set_verify_mode(ssl::verify_peer | ssl::verify_fail_if_no_peer_cert);
  socket.set_verify_callback([](bool preverified, verify_context &ctx) {
    std::cout << "verifying" << std::endl;
    return true;
  });
  auto endpoints = resolver_.resolve(target_ip, "33333");
  boost::asio::connect(socket.lowest_layer(), endpoints);
  socket.handshake(ssl::stream_base::client);
  return std::move(socket);
}

}  // namespace networking
}

;  // namespace chat_lib