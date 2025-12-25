#include "app_core/session_manager.h"

#include <algorithm>

#include "util/message.pb.h"

namespace chat_exec::core {

SessionManager::SessionManager(boost::asio::io_context& io_context)
    : io_context_(io_context) {}

chat_lib::session::chat_session* SessionManager::get_session(
    const std::string& remote_host_ip) {
  return sessions_[remote_host_ip].get();
}

void SessionManager::message_sent(const QString& msg) {
  auto displayed = chat_lib::util::sent_message(
      current_session_->get_local_address(), msg.toStdString());
  emit message_received(QString::fromStdString(displayed));
  current_session_->send_msg(msg.toStdString());
}

bool SessionManager::is_session_active(const std::string& remote_host_ip) {
  return (sessions_.find(remote_host_ip) != sessions_.end());
}

void SessionManager::close_session(const std::string& remote_host_ip) {
  sessions_[remote_host_ip]->stop();
  sessions_.erase(remote_host_ip);
}

void SessionManager::start_session(chat_lib::session::ssl_socket socket) {
  auto remote_host_ip =
      socket.lowest_layer().remote_endpoint().address().to_string();
  auto new_session = std::make_shared<chat_lib::session::chat_session>(
      io_context_, std::move(socket));

  {
    std::lock_guard<std::mutex> lock(mutex_);
    current_session_ = new_session;
    sessions_[remote_host_ip] = new_session;
  }

  new_session->listen_msg([this](const std::string& remote_endpoint,
                                 const chat_lib::util::ChatError err,
                                 const messages::ChatMessage& msg) {
    if (err == chat_lib::util::ChatError::REMOTE_HOST_DISCONNECT) {
      host_disconnect();
      close_session(remote_endpoint);
      return;
    }
    auto msg_content = chat_lib::util::msg_as_string(msg);
    message_received(QString::fromStdString(msg_content));
  });
}
}  // namespace chat_exec::core

/*
=========================================================================
LEARNING NOTES & IMPLEMENTATION DETAILS (For Future Reference)
=========================================================================

  [session_adapter and Q_OBJECT thread affinity]
  Previously another "adapter" class was used, to not make the session_manager
  a Q_OBJECT. That was done due to a misconception about Q_OBJECT's thread
  affinity and how resources are shared between different threads. The
  misconception was that, if Qt objects live on the thread which created
  them - in this case the main thread from chat_controller, then their resources
  could not be accessed from any different threads. That required leaving this
  class as a non-Q_OBJECT, and instead having a Q_OBJECT "adapter" class
  having the signals and slots. Turned out that it was a non-issue and
  different threads can access any resources which were created by different
  threads, since these

  [mutex]
  The start_session() method is accessed both from the main thread and the
  io_thread (see ChatController). We need to synchronize a portion of it with
  a mutex, since both threads could possibly add a new session to sessions_ at
  the same time, causing a data race. Same goes for the current_session_.
  lock_guard is just a RAII wrapper for the mutex object.

*/