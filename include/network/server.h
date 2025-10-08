//
// Created by rolandpwrrt on 7.10.2025.
//

#ifndef CHAT_APP_SERVER_H
#define CHAT_APP_SERVER_H
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "../core/session.h"

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> ssl_socket;

namespace networking {
  class Server {
  public:
    explicit Server(boost::asio::io_context& io_context);
    ~Server();
    std::shared_ptr<session::chat_session> create_session() ;

  private:
    boost::asio::io_context& io_context_;
    ssl::context ctx;
    tcp::socket socket_;
    tcp::acceptor acceptor_;
  };
}

#endif //CHAT_APP_SERVER_H