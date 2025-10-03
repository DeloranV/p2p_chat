//
// Created by rolandpwrrt on 7.10.2025.
//
#include "network/server.h"

namespace networking {
  p2p_server::p2p_server(boost::asio::io_context& io_context)
      : io_context_(io_context),
        socket_(tcp::socket(io_context)),
        acceptor_(tcp::acceptor(io_context, tcp::endpoint(tcp::v4(), 34567)))
    {}
    std::shared_ptr<session::chat_session> p2p_server::create_session() {
      acceptor_.accept(socket_);
      return std::make_shared<session::chat_session>(io_context_, socket_);
    }
  };