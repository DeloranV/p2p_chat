#include "app_core/session_adapter.h"

#include <boost/asio/io_context.hpp>

#include "chat_core/session.h"
#include "util/util.h"

namespace chat_exec {

namespace core {

SessionAdapter::SessionAdapter(boost::asio::io_context& io_context)
    : io_context_(io_context) {}

void SessionAdapter::register_session(
    chat_lib::session::chat_session* session) {
  session_ = session;
}

void SessionAdapter::deregister_session() { session_ = nullptr; }

void SessionAdapter::emit_host_disconnect() { emit host_disconnect(); }

void SessionAdapter::message_sent(const QString& msg) {
  auto displayed = chat_lib::util::sent_message(session_->get_local_address(),
                                                msg.toStdString());
  emit message_received(QString(displayed.c_str()));
  session_->send_msg(msg.toStdString());
}
}  // namespace core
}  // namespace chat_exec
