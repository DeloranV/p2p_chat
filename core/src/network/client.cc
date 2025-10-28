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
    ctx_.load_verify_file("../../ssl_test_keys_backup/server.crt");
    socket_.set_verify_mode(ssl::verify_peer);
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