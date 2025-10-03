//
// Created by rolandpwrrt on 7.10.2025.
//

#ifndef CHAT_APP_SERVER_H
#define CHAT_APP_SERVER_H
#include <boost/asio.hpp>
#include "../core/session.h"

using boost::asio::ip::tcp;

namespace networking {
  class p2p_server {
  public:
    explicit p2p_server(boost::asio::io_context& io_context);
    std::shared_ptr<session::chat_session> create_session() ;

  private:
    boost::asio::io_context& io_context_;
    tcp::socket socket_;
    tcp::acceptor acceptor_;
  };
}

#endif //CHAT_APP_SERVER_H