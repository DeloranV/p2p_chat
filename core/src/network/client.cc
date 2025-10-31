//
// Created by rolandpwrrt on 7.10.2025.
//
#include "network/client.h"
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ssl::verify_context;

namespace networking {
  Client::Client(boost::asio::io_context &io_context)
    : io_context_(io_context),
      ctx_(ssl::context::sslv23),
      socket_(tcp::socket(io_context), ctx_),
      resolver_(io_context) {
    //ctx_.set_default_verify_paths(); // TODO LATER THIS ON SERVER ?
    //ctx_.load_verify_file("../../ssl_test_keys_backup/server.crt");
    socket_.set_verify_mode(ssl::verify_peer | ssl::verify_fail_if_no_peer_cert);
    // SET VERIFY CALLBACK ONLY ON PEER SINCE THE PUBLIC KEY AND CERT ONLY GETS SENT SERVER -> CLIENT
    // THEN CLIENT CHECKS THE SERVER CERTIFICATE AND VERIFIES THE SERVER (WITH OUR CALLBACK)
    // THEN ENCRYPTS THE SESSION KEY WITH THE PUBLIC KEY
    // SENDS TO SERVER AND SERVERS DECRYPTS WITH ITS PRIVATE KEY AND THEN THE SESSION USES THE AGREED UPON KEY
    // https://docs.openssl.org/3.0/man3/SSL_CTX_set_verify/#notes - CHECK SSL_VERIFY_PEER IN CLIENT MODE
    // CLIENT MODE SINCE WE CALL THE HANDSHAKE AS A CLIENT
    // IF IT RETURN false AND WE INSPECT WITH WIRESHARK THEN WE CAN SEE THAT THE CLIENT SENDS AN
    // unknown CA ALERT AND TERMINATES THE SESSION
    socket_.set_verify_callback([](bool preverified, verify_context& ctx) {
      std::cout << "verifying" << std::endl;
      return false;
    });
  }

  ssl_socket&& Client::try_connect(std::string &target_ip) {
    auto endpoints = resolver_.resolve(target_ip, "33333");
    boost::asio::connect(socket_.lowest_layer(), endpoints);
    //socket_.set_verify_callback(ssl::host_name_verification("host.name"));  TODO ?
    socket_.handshake(ssl::stream_base::client);
    // std::move SINCE WE NEED TO TRANSFER OWNERSHIP OF THE SOCKET TO THE CALLER
    return std::move(socket_);
  }

};