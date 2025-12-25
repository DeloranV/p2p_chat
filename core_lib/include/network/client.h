#ifndef CHAT_APP_CLIENT_H
#define CHAT_APP_CLIENT_H
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

namespace chat_lib::networking {

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> ssl_socket;

/// @brief Manages the client-side connection logic.
/**
 * Handles the TCP/SSL handshake process, certificate verification and socket
 * lifecycle management
 */
class Client {
 public:
  explicit Client(boost::asio::io_context& io_context);

  /// @brief Establishes a connection to the target server.
  /**
   * @warning The current implementation overrides the verification callback
   *         to always return 'true'. This is strictly for development
   *         purposes and legitimate certificate verification will be
   *         implemented in the future since it's a MITM vulnerability.
   *
   * @param target_ip The IPv4 address of the chat server.
   * @return A ready to use, connected and verified ssl_socket.
   */
  [[nodiscard]] ssl_socket try_connect(const std::string& target_ip);

 private:
  boost::asio::io_context& io_context_;
  ssl::context ctx_;
  tcp::resolver resolver_;
};
}  // namespace chat_lib::networking

// namespace networking

#endif  // CHAT_APP_CLIENT_H