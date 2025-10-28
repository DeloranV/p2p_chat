#include "app_core/session_adapter.h"
#include <iostream>
#include <boost/asio/io_context.hpp>

#include "chat_core/session.h"
#include "util/util.h"

SessionAdapter::SessionAdapter(boost::asio::io_context& io_context)
  : io_context_(io_context)
{

}

void SessionAdapter::register_session(session::chat_session* session) {
  session_ = session;
}

void SessionAdapter::message_sent(QString msg) {
  // session_->display_sent(msg.toStdString());
  auto displayed = util::sent_message(session_->get_local_address(), msg.toStdString());
  emit message_received(QString(displayed.c_str()));
  session_->send_msg(msg.toStdString());
}
