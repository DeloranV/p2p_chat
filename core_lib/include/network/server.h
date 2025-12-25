#ifndef CHAT_APP_SERVER_H
#define CHAT_APP_SERVER_H
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <memory>

namespace chat_lib::networking {

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> ssl_socket;
using acceptor_handler_t = std::function<void(ssl_socket)>;

/// @brief A TCP server that asynchronously accepts incoming SSL/TLS connections
/**
 * @warning The current SSL configuration is for development purposes only and
 *          will be properly implemented in the future.
 *
 * @note The Server must be instantiated with
 *       @code std::make_shared<Server>@endcode
 *       to support @code shared_from_this()@endcode
 */
class Server : public std::enable_shared_from_this<Server> {
 public:
  explicit Server(boost::asio::io_context& io_context);
  ~Server();

  /// @brief Starts the asynchronous loop to accept incoming connections.
  /**
   * @param callback The handler to be called when a secure connection is
   *        established. It receives a connected and ready to use socket.
   *        Callback should have a following signature:
   *        @code void handler(ssl_socket)@endcode
   */
  void await_connection(const acceptor_handler_t& callback);

 private:
  void configure_tls();

  boost::asio::io_context& io_context_;
  ssl::context ctx;
  tcp::acceptor acceptor_;
};
}  // namespace chat_lib::networking

#endif  // CHAT_APP_SERVER_H