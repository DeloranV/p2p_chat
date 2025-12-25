#ifndef CHAT_APP_SESSION_H
#define CHAT_APP_SESSION_H

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <memory>

#include "util/message.pb.h"
#include "util/util.h"

namespace chat_lib::session {

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> ssl_socket;
using msg_handler_t =
    std::function<void(std::string, util::ChatError, messages::ChatMessage)>;

/// @brief Manages an active communication session with a peer.
class chat_session : public std::enable_shared_from_this<chat_session> {
 public:
  chat_session(boost::asio::io_context& io_context, ssl_socket socket);
  chat_session(chat_session&) = delete;
  chat_session(chat_session&&) noexcept;

  /// @brief Queues a message to be sent to the remote peer.
  /**
   * Send operation gets posted to the io_context thread.
   *
   * @param msg The plain text content of the message to send.
   */
  void send_msg(const std::string& msg);

  /// @brief Starts the asynchronous read loop.
  /**
   * @param handler A callback invoked on message receival or error. The handler
   * receives the remote host ip, error and the received message contents.
   * The handler signature is:
   * @code void(std::string ip, ChatError err, std::string)@endcode
   */

  void listen_msg(const msg_handler_t& handler);

  void stop();

  /// @brief Returns the IP address of the local machine.
  std::string get_local_address();

  /// @brief Returns the IP address of the connected remote peer.
  std::string get_remote_address();

 private:
  std::array<char, 128> rx_buf_;
  ssl_socket socket_;
  std::string remote_endpoint_address_;
  std::string last_received_msg;
  boost::asio::io_context& io_context_;
};
}  // namespace chat_lib::session

#endif  // CHAT_APP_SESSION_H