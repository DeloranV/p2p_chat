//
// Created by rolandpwrrt on 7.10.2025.
//

#ifndef CHAT_APP_CLIENT_H
#define CHAT_APP_CLIENT_H
#include <boost/asio.hpp>
#include "../core/session.h"

using boost::asio::ip::tcp;

namespace networking {
  class p2p_client {
  public:
    explicit p2p_client(boost::asio::io_context& io_context);
    std::shared_ptr<session::chat_session> create_session(std::string& target_ip);

  private:
    boost::asio::io_context& io_context_;
    tcp::resolver resolver_;
    tcp::socket socket_;
  };
}

#endif //CHAT_APP_CLIENT_H