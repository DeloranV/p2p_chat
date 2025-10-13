//
// Created by rolandpwrrt on 7.10.2025.
//

#ifndef CHAT_APP_APP_H
#define CHAT_APP_APP_H

#include <memory>
#include <QObject>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "cli/cli.h"
#include "network/network.h"
#include "util/util.h"
#include "gui/gui_manager.hpp"
#include "core/session_adapter.h"

class ChatController : public QObject {
  Q_OBJECT
public:
  explicit ChatController(boost::asio::io_context& io_context);
  void run();

public slots:
  void start_client();
  void start_server();

signals:
  void client_connected();

private:
  boost::asio::io_context& io_context_;
  boost::thread chat_thread_;
  std::unique_ptr<GuiManager> gui_manager_;
  std::shared_ptr<networking::Server> server_;
  std::shared_ptr<networking::Client> client_;
  std::shared_ptr<session::chat_session> session_;
  std::shared_ptr<SessionAdapter> adapter_;
};

#endif //CHAT_APP_APP_H