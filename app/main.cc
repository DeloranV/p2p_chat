#include <QApplication>
#include <boost/asio.hpp>

#include "include/app_core/chat_controller.h"

int main(int argc, char* argv[]) {
  boost::asio::io_context io_context;
  QApplication a(argc, argv);
  chat_exec::core::ChatController chat(io_context);
  chat.run();
  return QApplication::exec();
}