//
// Created by rolandpwrrt on 7.10.2025.
//

#ifndef CHAT_APP_APP_H
#define CHAT_APP_APP_H

#include <memory>
#include <QObject>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "network/network.h"
#include "util/util.h"
#include "session_adapter.h"
#include "app_core/session_manager.h"
#include "gui/gui_manager.hpp"

class ChatController : public QObject {
  Q_OBJECT
public:
  explicit ChatController(boost::asio::io_context& io_context);
  void run();
  ~ChatController();

public slots:
  void start_client();
  void start_server();
  void open_chat(std::string target_ip);

signals:
  void chat_window_opened();

private:
  boost::asio::io_context& io_context_;
  boost::thread server_thread_;
  boost::thread client_thread_;
  std::unique_ptr<GuiManager> gui_manager_;
  std::shared_ptr<SessionAdapter> adapter_;
  std::shared_ptr<SessionManager> session_manager_;
  std::shared_ptr<networking::Server> server_;
  std::shared_ptr<networking::Client> client_;
};

#endif //CHAT_APP_APP_H