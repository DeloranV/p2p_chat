//
// Created by rolandpwrrt on 18.10.2025.
//

#ifndef CHAT_APP_SESSION_ADAPTER_H
#define CHAT_APP_SESSION_ADAPTER_H

#include <QObject>
#include <functional>
#include <boost/asio/io_context.hpp>

namespace session { class chat_session; }

// CLASS SERVING AS AN ADAPTER
// BETWEEN boost::asio ORIENTED SESSION AND Qt GUI
class SessionAdapter : public QObject {
  Q_OBJECT
public:
  SessionAdapter(boost::asio::io_context& io_context);
  void register_session(session::chat_session* session);

  boost::asio::io_context& io_context_;
  session::chat_session* session_;

public slots:
  void message_sent(QString msg);

signals:
  void message_received(QString msg);
};


#endif //CHAT_APP_SESSION_ADAPTER_H