#include "gui/chat_window.hpp"

ChatWindow::ChatWindow() {
    chat_window.setupUi(this);
}

void ChatWindow::somefunc() {

}

QPushButton* ChatWindow::get_SEND_button() const {
    return chat_window.pushButton;
}

QLineEdit* ChatWindow::get_message_line_edit() const {
    return chat_window.lineEdit;
}

QListWidget* ChatWindow::get_chat_history() const {
    return chat_window.listWidget;
}

QString ChatWindow::get_message() const {
    auto msg_line = get_message_line_edit();
    auto msg = msg_line->text();
    msg_line->clear();
    return msg;
}

void ChatWindow::display_message(std::string msg) {
    new QListWidgetItem(QString(msg.c_str()), get_chat_history());
}

