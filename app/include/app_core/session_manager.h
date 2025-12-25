#ifndef CHAT_APP_SESSION_MANAGR_H
#define CHAT_APP_SESSION_MANAGR_H

#include <QObject>
#include <mutex>

#include "chat_core/session.h"

namespace chat_exec::core {

/// @brief Manages the lifecycle and state of active chat sessions.
/**
 * Responsible for creating, storing and safely destroying session objects
 * when connections are established or lost
 */
class SessionManager : public QObject {
  Q_OBJECT

 public:
  explicit SessionManager(boost::asio::io_context& io_context);

  void start_session(chat_lib::session::ssl_socket socket);
  void close_session(const std::string& remote_host_ip);
  [[nodiscard]] chat_lib::session::chat_session* get_session(
      const std::string& remote_host_ip);
  [[nodiscard]] bool is_session_active(const std::string& remote_host_ip);

 public slots:
  void message_sent(const QString& msg);

 signals:
  void message_received(QString msg);
  void host_disconnect();

 private:
  boost::asio::io_context& io_context_;
  std::mutex mutex_;
  std::unordered_map<std::string,
                     std::shared_ptr<chat_lib::session::chat_session>>
      sessions_;
  std::shared_ptr<chat_lib::session::chat_session> current_session_;
};

}  // namespace chat_exec::core

#endif  // CHAT_APP_SESSION_MANAGR_H