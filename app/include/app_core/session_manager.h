#ifndef P2P_CHAT_APP_APP_CORE_SESSION_MANAGER_H_
#define P2P_CHAT_APP_APP_CORE_SESSION_MANAGER_H_

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

  void StartSession(chat_lib::session::SSLSocket socket);
  void CloseSession(const std::string& remote_host_ip);
  [[nodiscard]] chat_lib::session::ChatSession* GetSession(
      const std::string& remote_host_ip);
  [[nodiscard]] bool IsSessionActive(const std::string& remote_host_ip);

 public slots:
  void MessageSent(const QString& msg);

 signals:
  void MessageReceived(QString msg);
  void HostDisconnect();

 private:
  boost::asio::io_context& io_context_;
  std::mutex mutex_;
  std::unordered_map<std::string,
                     std::shared_ptr<chat_lib::session::ChatSession>>
      sessions_;
  std::shared_ptr<chat_lib::session::ChatSession> current_session_;
};

}  // namespace chat_exec::core

#endif  // P2P_CHAT_APP_APP_CORE_SESSION_MANAGER_H_