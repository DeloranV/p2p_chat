//
// Created by rolandgugalapwrrt on 17.10.25.
//

#ifndef GUI_MANAGER_HPP
#define GUI_MANAGER_HPP

#include <memory>
#include <stack>
#include <string>
#include <QtWidgets/QApplication>
// TODO MOVE THESE INCLUDES TO A SINGLE .H FILE ui/ui_elements.h AND INCLUDE THAT
#include "view.h"
#include "main_menu.h"
#include "add_host.h"
#include "gui/unavailable.h"
#include "chat_window.hpp"
#include "gui/disconnect.h"

class GuiManager : public QObject {
    Q_OBJECT
public:
    GuiManager();
    std::string get_host_ip() const;
    void go_into(AbstractView* dst);

public slots:
    void open_main_menu();
    void open_chat_window();
    void open_unavailable();
    void open_host_disconnected();
    void open_add_host();
    void emit_sent_msg();
    void display_received_msg(QString msg);
    void new_host_added();
    void go_back_to_menu();
    void go_back();

    void chat_window_opened_wrapper();

signals:
    void chat_window_opened(std::string target_ip);
    void message_sent(QString msg);

private:
    // TODO "NAVIGATOR" STACK - PUSH WHEN GOING TO NEW VIEW AND POP WHEN GOING BACK (NEEDS A BACK BUTTON IN UI)
    // stack by default uses .push() .pop() and .top() from an underlying std::deque which is a container class
    // which means that pushing will create a copy of the pushed data inside of the underlying container
    // we don't want to create copies of abstractviews just for navigation tracking
    // so we pass the pointers to them instead to have them hold copies of pointers to their addresses
    // (as if we passed a reference to them, but we can't since they're dynamically allocated)
    std::stack<AbstractView*> nav_stack_;   // TODO CHANE UNIQUEPTR TO THE QT PARENT CHILD OWNERSHIP ?
    std::unique_ptr<ChatWindow> chat_window_;
    std::unique_ptr<MainMenu> main_menu_;
    std::unique_ptr<Unavailable> unavailable_;
    std::unique_ptr<Disconnect> disconnect_;
    std::unique_ptr<AddHost> add_host_;
};

#endif //GUI_MANAGER_HPP
