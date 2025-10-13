#include "core/session_adapter.h"
#include <iostream>
#include <boost/asio/io_context.hpp>

#include "core/session.h"

SessionAdapter::SessionAdapter(boost::asio::io_context& io_context)
  : io_context_(io_context)
{

}

void SessionAdapter::register_session(std::shared_ptr<session::chat_session> session) {
  session_ = session;
}

void SessionAdapter::message_sent(QString msg) {
  session_->display_sent(msg.toStdString());
  session_->send_msg(msg.toStdString());
}


