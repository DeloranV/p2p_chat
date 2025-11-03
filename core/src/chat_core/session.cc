#include "chat_core/session.h"

#include <array>
#include <boost/bind.hpp>
#include <string>

#include "util/util.h"

namespace chat_lib {

namespace session {

// SOCKET TAKEN BY RVALUE SINCE SESSION WILL BE THE OWNER
// OWNERSHIP OF SOCKET PASSED BY VALUE FOR VERSATILE API - WILL ACCEPT BOTH
// LVALUE AND RVALUE INSTEAD OF JUST RVAL
chat_session::chat_session(boost::asio::io_context& io_context,
                           ssl_socket socket)
    : socket_(std::move(socket)),
      remote_endpoint_address_(
          socket_.lowest_layer().remote_endpoint().address().to_string()),
      io_context_(io_context) {}

chat_session::~chat_session() {
  socket_.lowest_layer().shutdown(tcp::socket::shutdown_both);
  socket_.lowest_layer().close();
}

chat_session::chat_session(chat_session&& session) noexcept
    : socket_(std::move(session.socket_)),
      remote_endpoint_address_(std::move(session.remote_endpoint_address_)),
      io_context_(io_context_)

{}

std::string chat_session::get_local_address() {
  return socket_.lowest_layer().local_endpoint().address().to_string();
}

std::string chat_session::get_remote_address() {
  return remote_endpoint_address_;
}

// CALLBACK FOR CLI_MANAGER - CONSOLE THREAD FROM CLI_manager::await_input
// CANNOT DIRECTLY CALL socket_.write_some() WE NEED TO POST THE CALLBACK TO
// io_context EVENT LOOP
void chat_session::send_msg(const std::string& msg) {
  io_context_.post(std::bind(&chat_session::do_send_msg, this, msg));
}

void chat_session::do_send_msg(const std::string& msg) {
  boost::system::error_code error;
  std::string payload = util::serialize_message(remote_endpoint_address_, msg);

  socket_.write_some(boost::asio::buffer(payload), error);
}

void chat_session::listen_msg(const msg_handler_t& handler) {
  socket_.async_read_some(
      boost::asio::buffer(rx_buf_),
      boost::bind(&chat_session::save_received, this,
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred, handler));
}

void chat_session::save_received(const boost::system::error_code& error,
                                 std::size_t bytes_transferred,
                                 const msg_handler_t& handler) {
  auto err_c = util::translate_error(error);
  if (err_c != util::ChatError::OK) {
    handler(remote_endpoint_address_, err_c, {});
    return;
  }
  std::string buffer_data = rx_buf_.data();
  // WHEN MESSAGE IS READ FROM A SOCKET IT FILLS THE BUFFER FROM THE BEGINNING
  // UP TO THE LENGTH OF THE MSG ...
  // ...OVERWRITING THE PREVIOUS CHARACTERS - IF CURRENT MESSAGE IS SHORTER THAN
  // PREVIOUS THEN THERE WILL BE ...
  // ...A PART OF THE OLDER MESSAGE STILL IN THE BUFFER
  std::string serialized = buffer_data.substr(0, bytes_transferred);
  auto deserialized = util::deserialize_message(serialized);
  handler(remote_endpoint_address_, err_c, deserialized);
  listen_msg(handler);
}
}  // namespace session
}  // namespace chat_lib
