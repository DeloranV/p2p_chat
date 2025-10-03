//
// Created by rolandpwrrt on 7.10.2025.
//
#include "network/client.h"
#include <boost/asio.hpp>

namespace networking {
   p2p_client::p2p_client(boost::asio::io_context& io_context)
    : io_context_(io_context),
      socket_(tcp::socket(io_context)),
      resolver_(tcp::resolver(io_context))
  {}

  std::shared_ptr<session::chat_session> p2p_client::create_session(std::string& target_ip) {
    auto endpoints = resolver_.resolve(target_ip, "34567");
    boost::asio::connect(socket_, endpoints);
    return std::make_shared<session::chat_session>(io_context_, socket_);
  }

};