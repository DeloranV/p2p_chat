#include <iostream>
#include <boost/asio.hpp>
#include "include/app_core/chat_controller.h"
#include <QApplication>

// FOR MULTIPLE CHAT SESSIONS - DO A VECTOR OF CHAT SESSIONS AND PASS OWNERSHIP OF SOCKETS TO THEM ?
// DO A SESSION MANAGER OBJECT HOLDING AND MANAGING THE SESSIONS - THEN SERVER AND CLIENT WOULD HOLD ONLY THE MANAGER
// DO A CLI MANAGER FOR CONSOLE INPUT/OUTPUT
// DO ENCRYPTION WITH BOOST

int main(int argc, char* argv[]) {
  boost::asio::io_context io_context;
  QApplication a(argc, argv);
  ChatController chat (io_context);
  chat.run();
  return QApplication::exec();
}