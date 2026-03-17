#include "gui/chat_window.h"

namespace chat_exec::gui {

ChatWindow::ChatWindow() : chat_window() {
  chat_window.setupUi(this);
  SetupConnections();
}

QString ChatWindow::GetMessage() const {
  auto msg_line = chat_window.message_line_edit;
  auto msg = msg_line->text();
  msg_line->clear();
  return msg;
}

void ChatWindow::DisplayMessage(std::string msg) {
  new QListWidgetItem(QString::fromStdString(msg), chat_window.chat_history);
}

void ChatWindow::SetupConnections() {
  connect(chat_window.send_button, &QPushButton::clicked, this,
          &ChatWindow::SendBttnClicked);
}
}  // namespace chat_exec::gui
