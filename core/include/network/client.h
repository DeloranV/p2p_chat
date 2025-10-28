//
// Created by rolandpwrrt on 7.10.2025.
//

#ifndef CHAT_APP_CLIENT_H
#define CHAT_APP_CLIENT_H
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> ssl_socket;

namespace networking {
  class Client {
  public:
    explicit Client(boost::asio::io_context& io_context);
    [[nodiscard]] ssl_socket&& try_connect(std::string& target_ip);

  private:
    // TODO LEGITIMATE CERTIFICATE VERIFICATION
    // bool verify_certificate(bool preverified, ssl::verify_context& ctx);

    boost::asio::io_context& io_context_;
    ssl::context ctx_;
    tcp::resolver resolver_;
    ssl_socket socket_;
  };
}

#endif //CHAT_APP_CLIENT_H