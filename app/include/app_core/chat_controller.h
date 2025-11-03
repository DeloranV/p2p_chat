#ifndef CHAT_APP_APP_H
#define CHAT_APP_APP_H

#include <QObject>
#include <boost/asio.hpp>
#include <memory>

#include "app_core/session_manager.h"
#include "gui/gui_manager.hpp"
#include "network/network.h"
#include "session_adapter.h"

namespace chat_exec {

namespace core {

class ChatController : public QObject {
  Q_OBJECT
 public:
  explicit ChatController(boost::asio::io_context& io_context);
  void run();
  ~ChatController() override;

 public slots:
  void start_client();
  void start_server();
  void open_chat(const std::string& target_ip);

 signals:
  void chat_window_opened();

 private:
  boost::asio::io_context& io_context_;
  std::thread server_thread_;
  std::thread client_thread_;
  std::unique_ptr<gui::GuiManager> gui_manager_;
  std::shared_ptr<SessionAdapter> adapter_;
  std::shared_ptr<SessionManager> session_manager_;
  std::shared_ptr<chat_lib::networking::Server> server_;
  std::shared_ptr<chat_lib::networking::Client> client_;
};
}  // namespace core

}  // namespace chat_exec

#endif  // CHAT_APP_APP_H