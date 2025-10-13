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
#include "gui/view.h"
#include "gui/program_mode.h"
#include "gui/ip_port_prompt.hpp"
#include "gui/port_prompt.hpp"
#include "gui/server_listen_connection.hpp"
#include "gui/chat_window.hpp"

class GuiManager : public QObject {
    Q_OBJECT
public:
    GuiManager();
    PortPrompt& getPortPrompt() const;
    IpPortPrompt& getIpPortPrompt() const;
public slots:
    void open_port_prompt();
    void open_program_mode();
    void open_ip_port_prompt();
    void open_chat_window();
    void open_server_listen_connection();
    void emit_sent_msg();
    void display_received_msg(QString msg);

signals:
    void server_port_given();
    void client_ip_port_given();
    void message_sent(QString msg);

private:
    void go_into(AbstractView* dst);
    // TODO "NAVIGATOR" STACK - PUSH WHEN GOING TO NEW VIEW AND POP WHEN GOING BACK (NEEDS A BACK BUTTON IN UI)
    // stack by default uses .push() .pop() and .top() from an underlying std::deque which is a container class
    // which means that pushing will create a copy of the pushed data inside of the underlying container
    // we don't want to create copies of abstractviews just for navigation tracking
    // so we pass the pointers to them instead to have them hold copies of pointers to their addresses
    // (as if we passed a reference to them, but we can't since they're dynamically allocated)
    std::stack<AbstractView*> nav_stack_;
    std::unique_ptr<ChatWindow> chat_window_;
    std::unique_ptr<IpPortPrompt> ip_port_prompt_;
    std::unique_ptr<PortPrompt> port_prompt_;
    std::unique_ptr<ProgramMode> program_mode_;
    std::unique_ptr<ServerListenConnection> server_listen_connection_;

};

#endif //GUI_MANAGER_HPP
