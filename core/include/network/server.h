#ifndef CHAT_APP_SERVER_H
#define CHAT_APP_SERVER_H
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> ssl_socket;

namespace chat_lib {

namespace networking {

using acceptor_handler_t = std::function<void(ssl_socket)>;

class Server {
 public:
  explicit Server(boost::asio::io_context& io_context);
  ~Server();
  void await_connection(const acceptor_handler_t& callback);

 private:
  void configure_tls();
  void handle_accept(const boost::system::error_code& error,
                     const acceptor_handler_t& callback);

  boost::asio::io_context& io_context_;
  ssl::context ctx;
  tcp::socket socket_;
  tcp::acceptor acceptor_;
};
}  // namespace networking
}  // namespace chat_lib

#endif  // CHAT_APP_SERVER_H