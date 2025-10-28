//
// Created by rolandpwrrt on 7.10.2025.
//

#ifndef CHAT_APP_SERVER_H
#define CHAT_APP_SERVER_H
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> ssl_socket;

namespace networking {
  class Server {
  public:
    explicit Server(boost::asio::io_context& io_context);
    ~Server();
    void await_connection(std::function<void(ssl_socket)> callback) ;

  private:
    void configure_tls();
    void handle_accept(const boost::system::error_code& error, std::function<void(ssl_socket)> callback);

    boost::asio::io_context& io_context_;
    ssl::context ctx;
    tcp::socket socket_;
    tcp::acceptor acceptor_;
  };
}

#endif //CHAT_APP_SERVER_H