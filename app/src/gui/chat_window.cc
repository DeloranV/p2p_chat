#include "gui/chat_window.h"

namespace chat_exec::gui {

ChatWindow::ChatWindow() : chat_window() {
  chat_window.setupUi(this);
  setup_connections();
}

QString ChatWindow::get_message() const {
  auto msg_line = chat_window.message_line_edit;
  auto msg = msg_line->text();
  msg_line->clear();
  return msg;
}

void ChatWindow::display_message(std::string msg) {
  new QListWidgetItem(QString::fromStdString(msg), chat_window.chat_history);
}

void ChatWindow::setup_connections() {
  connect(chat_window.send_button, &QPushButton::clicked, this,
          &ChatWindow::send_bttn_clicked);
}
}  // namespace chat_exec::gui
