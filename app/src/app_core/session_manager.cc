#include "app_core/session_manager.h"
#include <iostream>
#include <algorithm>

SessionManager::SessionManager(boost::asio::io_context& io_context, std::shared_ptr<SessionAdapter> adapter)
  : io_context_(io_context),
    adapter_(adapter)
{
}

session::chat_session* SessionManager::get_session(std::string remote_host_ip) {
  auto sesssion = std::find_if(sessions_.begin(), sessions_.end(),
    [remote_host_ip](session::chat_session& session_it) {
      return session_it.get_remote_address() == remote_host_ip;
  });
  return sesssion.base();
}

// IF A SESSION IS ACTIVE IT MEANS ITS IN OUR VECTOR OF SESSIONS
// AS SOON AS A SESSION IS ENDED IT GETS DESTROYED AND FREES UP SPACE IN THE VECTOR
bool SessionManager::is_session_active(std::string remote_host_ip) {
  auto count = std::any_of(sessions_.begin(), sessions_.end(),
    [remote_host_ip](session::chat_session& session_it) {
      return session_it.get_remote_address() == remote_host_ip;
    });
  return count > 0;
}

void SessionManager::temp_handler(std::string msg) {
  adapter_->message_received(msg.c_str());
}

void SessionManager::start_session(ssl_socket socket, SessionAdapter& adapter) {
  //session_started = true;
  // GET IP BEFORE WE MOVE THE SOCKET
  auto remote_host_ip = socket.lowest_layer().remote_endpoint().address().to_string();
  sessions_.emplace_back(io_context_, std::move(socket));
  auto created_session = get_session(remote_host_ip);
  //auto created_session = sessions_.end()--; // TODO ITERATORS CAN GET INVALIDATED ?
  // single_session_ = std::make_shared<session::chat_session>(io_context_, std::move(socket));
  adapter.register_session(created_session);
  // TODO find out how we would do it with a std::bind - with a lambda we're capturing *this to get access to the
  // adapter inside of the handler, but if we did it with a std::bind, would we not have to pass *this as additional
  // argument, which in turn would require us to change the signature of the taken handler to void(std::string, SessionManager)?
  created_session->listen_msg(std::bind(&SessionManager::temp_handler, this, std::placeholders::_1)); // WHY DOES THIS WORK ??
}
