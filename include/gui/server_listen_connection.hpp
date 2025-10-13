//
// Created by rolandgugalapwrrt on 17.10.25.
//

#ifndef SERVER_LISTEN_CONNECTION_HPP
#define SERVER_LISTEN_CONNECTION_HPP

#include "gui/view.h"
#include "ui/ui_server_listen_connection.h"

class ServerListenConnection : public AbstractView {
public:
    ServerListenConnection();
    void somefunc() override;
private:
    Ui::server_listen_connection_widget server_listen_connection;
};

#endif //SERVER_LISTEN_CONNECTION_HPP
