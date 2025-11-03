#ifndef CHAT_APP_CLIENT_H
#define CHAT_APP_CLIENT_H
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> ssl_socket;

namespace chat_lib {

namespace networking {

class Client {
 public:
  explicit Client(boost::asio::io_context& io_context);
  [[nodiscard]] ssl_socket try_connect(const std::string& target_ip);

 private:
  boost::asio::io_context& io_context_;
  ssl::context ctx_;
  tcp::resolver resolver_;
};
}  // namespace networking

}  // namespace chat_lib

// namespace networking

#endif  // CHAT_APP_CLIENT_H