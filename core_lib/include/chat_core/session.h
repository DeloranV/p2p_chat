#ifndef P2P_CHAT_CORE_LIB_CHAT_CORE_SESSION_H_
#define P2P_CHAT_CORE_LIB_CHAT_CORE_SESSION_H_

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <memory>

#include "util/message.pb.h"
#include "util/util.h"

namespace chat_lib::session {

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> SSLSocket;
using MsgHandler =
    std::function<void(std::string, util::ChatError, messages::ChatMessage)>;

/// @brief Manages an active communication session with a peer.
class ChatSession : public std::enable_shared_from_this<ChatSession> {
 public:
  ChatSession(boost::asio::io_context& io_context, SSLSocket socket);
  ChatSession(ChatSession&) = delete;
  ChatSession(ChatSession&&) noexcept;

  /// @brief Queues a message to be sent to the remote peer.
  /**
   * Send operation gets posted to the io_context thread.
   *
   * @param msg The plain text content of the message to send.
   */
  void SendMsg(const std::string& msg);

  /// @brief Starts the asynchronous read loop.
  /**
   * @param handler A callback invoked on message receival or error. The handler
   * receives the remote host ip, error and the received message contents.
   * The handler signature is:
   * @code void(std::string ip, ChatError err, std::string)@endcode
   */

  void ListenMsg(const MsgHandler& handler);

  void Stop();

  /// @brief Returns the IP address of the local machine.
  std::string GetLocalAddress();

  /// @brief Returns the IP address of the connected remote peer.
  std::string GetRemoteAddress();

 private:
  std::array<char, 128> rx_buf_;
  SSLSocket socket_;
  std::string remote_endpoint_address_;
  std::string last_received_msg_;
  boost::asio::io_context& io_context_;
};
}  // namespace chat_lib::session

#endif  // P2P_CHAT_CORE_LIB_CHAT_CORE_SESSION_H_