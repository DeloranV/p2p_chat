//
// Created by rolandgugalapwrrt on 17.10.25.
//

#ifndef CHAT_WINDOW_HPP
#define CHAT_WINDOW_HPP

#include "view.h"
#include "ui/ui_chat_window.h"

class ChatWindow : public AbstractView {
public:
    ChatWindow();
    void somefunc() override;
    void display_message(std::string msg);
    QString get_message() const;
    QListWidget* get_chat_history() const;
    QLineEdit* get_message_line_edit() const;
    QPushButton* get_SEND_button() const;

    Ui::chat_window chat_window;
};
#endif //CHAT_WINDOW_HPP
