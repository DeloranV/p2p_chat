#ifndef P2P_CHAT_CORE_LIB_NETWORK_SERVER_H_
#define P2P_CHAT_CORE_LIB_NETWORK_SERVER_H_
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <memory>

namespace chat_lib::networking {

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> SSLSocket;
using AcceptorHandler = std::function<void(SSLSocket)>;

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
  void AwaitConnection(const AcceptorHandler& callback);

 private:
  void ConfigureTLS();

  boost::asio::io_context& io_context_;
  ssl::context ctx_;
  tcp::acceptor acceptor_;
};
}  // namespace chat_lib::networking

#endif  // P2P_CHAT_CORE_LIB_NETWORK_SERVER_H_