#include "chat_core/session.h"

#include <array>
#include <string>

#include "util/util.h"

namespace chat_lib::session {

chat_session::chat_session(boost::asio::io_context& io_context,
                           ssl_socket socket)
    : socket_(std::move(socket)),
      remote_endpoint_address_(
          socket_.lowest_layer().remote_endpoint().address().to_string()),
      io_context_(io_context),
      rx_buf_() {}

void chat_session::stop() {
  socket_.lowest_layer().shutdown(tcp::socket::shutdown_both);
  socket_.lowest_layer().close();
}

chat_session::chat_session(chat_session&& session) noexcept
    : socket_(std::move(session.socket_)),
      remote_endpoint_address_(std::move(session.remote_endpoint_address_)),
      io_context_(session.io_context_),
      rx_buf_(session.rx_buf_) {}

std::string chat_session::get_local_address() {
  return socket_.lowest_layer().local_endpoint().address().to_string();
}

std::string chat_session::get_remote_address() {
  return remote_endpoint_address_;
}

void chat_session::send_msg(const std::string& msg) {
  io_context_.post([shared_this = shared_from_this(), msg] {
    boost::system::error_code error;
    std::string payload =
        util::serialize_message(shared_this->get_local_address(), msg);

    shared_this->socket_.write_some(boost::asio::buffer(payload), error);
  });
}

void chat_session::listen_msg(const msg_handler_t& handler) {
  socket_.async_read_some(
      boost::asio::buffer(rx_buf_), [shared_this = shared_from_this(), handler](
                                        const boost::system::error_code& error,
                                        std::size_t bytes_transferred) {
        auto err_c = util::translate_error(error);
        if (err_c != util::ChatError::OK) {
          handler(shared_this->remote_endpoint_address_, err_c, {});
          return;
        }
        std::string serialized(shared_this->rx_buf_.data(), bytes_transferred);
        auto deserialized = util::deserialize_message(serialized);
        handler(shared_this->remote_endpoint_address_, err_c, deserialized);
        shared_this->listen_msg(handler);
      });
}
}  // namespace chat_lib::session

/*
=========================================================================
LEARNING NOTES & IMPLEMENTATION DETAILS (For Future Reference)
=========================================================================

  [Rx message buffer]
  Whenever a message arrives into the buffer, the async_read_some callback
  gets executed and the number of received bytes is passed inside. Since each
  character is one byte, it effectively tells us the length of the received
  message. We can then use that to know how many bytes should be read from
  the buffer when passing the received string into the user-given handler.

  The rx_buf works in a way where its contents get overwritten with incoming
  characters, starting from 0 up to the length of the incoming message. We read
  only the number of characters that were currently received, to not read any
  stale data from the buffer.
  Example:
    previously received message: "Hey there!"
    currently received message: "Hello"
    rx_buf contents: "Hellohere!"

  [Sending a message by io_context.post()]
  Instead of directly writing to the socket itself, we enqueue the operation
  on the io_context event queue where it will be picked by a worker thread/pool
  that called io_context.run(). This is necessary due to the fact, that the
  socket operations can only be done by the threads which have access to the
  io_context which was given during the socket construction. If the method
  did a direct write to the socket, the user could possibly call it from a
  different thread which has no access to that socket/io_context, which would
  result in a segfault.

  [Move/copy constructors]
  Copy constructor has been deleted since Session is made-up of non-copyable
  members, such as the socket. For this reason, it's more fitting to make
  the Session instance moveable only.

  [shared_from_this]
  A shared *this is used to ensure that the Session instance will be alive for
  as long as there is a pending message read/write. Without it, if the object
  was destroyed while there were still messages to be received/sent, the
  program would crash. Instead, shared_from_this prevents destruction until
  the operations complete. However, now whenever a Session is created it needs
  to be contained inside a shared_ptr to support the shared ownership semantics.

  [.stop() + default destructor]
  A default destructor is sufficent, since it destroys the RAII ssl_socket
  object, whose destructor automatically closes the socket.

  A .stop() method is necessary to cancel any pending listen/send operations.
  These operations closures hold shared_this, which extends the session lifetime
  as long as they are pending in the io_context. We need to bring the reference
  count to 0 for the session to be destroyed, therefore closing the socket will
  cancel these operations and destroy the closures holding the shared pointers.
*/