#ifndef CHAT_APP_SESSION_ADAPTER_H
#define CHAT_APP_SESSION_ADAPTER_H

#include <QObject>
#include <boost/asio/io_context.hpp>

#include "chat_core/session.h"

namespace chat_exec {

namespace core {

// CLASS SERVING AS AN ADAPTER
// BETWEEN boost::asio ORIENTED SESSION AND Qt GUI
class SessionAdapter : public QObject {
  Q_OBJECT
 public:
  explicit SessionAdapter(boost::asio::io_context& io_context);
  void register_session(chat_lib::session::chat_session* session);
  void deregister_session();
  void emit_host_disconnect();

  boost::asio::io_context& io_context_;
  chat_lib::session::chat_session* session_;

 public slots:
  void message_sent(const QString& msg);

 signals:
  void message_received(QString msg);
  void host_disconnect();
};
}  // namespace core
}  // namespace chat_exec

#endif  // CHAT_APP_SESSION_ADAPTER_H