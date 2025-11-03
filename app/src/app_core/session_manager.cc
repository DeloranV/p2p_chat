#include "app_core/session_manager.h"

#include <algorithm>

#include "util/message.pb.h"

namespace chat_exec {

namespace core {

SessionManager::SessionManager(boost::asio::io_context& io_context,
                               std::shared_ptr<SessionAdapter> adapter)
    : io_context_(io_context), adapter_(adapter) {}

chat_lib::session::chat_session* SessionManager::get_session(
    std::string remote_host_ip) {
  auto sesssion = std::find_if(
      sessions_.begin(), sessions_.end(),
      [remote_host_ip](
          const std::unique_ptr<chat_lib::session::chat_session>& session_it) {
        return session_it->get_remote_address() == remote_host_ip;
      });
  return sesssion.base()->get();
}

// IF A SESSION IS ACTIVE IT MEANS IT'S IN OUR VECTOR OF SESSIONS
// AS SOON AS A SESSION IS ENDED IT GETS DESTROYED AND FREES UP SPACE IN THE
// VECTOR
bool SessionManager::is_session_active(std::string remote_host_ip) {
  auto count = std::any_of(
      sessions_.begin(), sessions_.end(),
      [remote_host_ip](
          const std::unique_ptr<chat_lib::session::chat_session>& session_it) {
        return session_it->get_remote_address() == remote_host_ip;
      });
  return count > 0;
}

void SessionManager::close_session(std::string remote_host_ip) {
  sessions_.erase(std::find_if(
      sessions_.begin(), sessions_.end(),
      [remote_host_ip](
          const std::unique_ptr<chat_lib::session::chat_session>& session_it) {
        return session_it->get_remote_address() == remote_host_ip;
      }));
}

void SessionManager::start_session(ssl_socket socket, SessionAdapter& adapter) {
  auto remote_host_ip =
      socket.lowest_layer().remote_endpoint().address().to_string();
  sessions_.emplace_back(std::make_unique<chat_lib::session::chat_session>(
      io_context_, std::move(socket)));
  auto created_session = get_session(remote_host_ip);
  adapter.register_session(created_session);

  created_session->listen_msg([this](const std::string& remote_endpoint,
                                     const chat_lib::util::ChatError err,
                                     const messages::ChatMessage& msg) {
    if (err == chat_lib::util::ChatError::REMOTE_HOST_DISCONNECT) {
      adapter_->emit_host_disconnect();
      adapter_->deregister_session();
      close_session(remote_endpoint);
      return;
    }
    auto msg_content = msg.msg_contents();
    adapter_->message_received(msg_content.c_str());
  });
}
}  // namespace core
}  // namespace chat_exec
