#ifndef P2P_CHAT_APP_APP_CORE_CHAT_CONTROLLER_H_
#define P2P_CHAT_APP_APP_CORE_CHAT_CONTROLLER_H_

#include <boost/asio.hpp>
#include <memory>

#include "app_core/session_manager.h"
#include "gui/gui_manager.h"
#include "network/client.h"
#include "network/server.h"

namespace chat_exec::core {

/// @brief Central orchestrator of the chat application executable.
/**
 * Implements the Mediator pattern, binding together GUI and Networking.
 * Responsible for managing the application lifecycle, background networking
 * thread and connecting GUI signals to networking slots.
 *
 * @note This class lives on the Main Thread but manages the background IO
 * networking thread.
 */
class ChatController : public QObject {
  Q_OBJECT
 public:
  explicit ChatController(boost::asio::io_context& io_context);
  void Run();
  ~ChatController() override;

 public slots:
  void StartClient();
  void SetupServer();
  void OpenChat(const std::string& target_ip);

 signals:
  void ChatWindowOpened();

 private:
  void StartIOContext();

  boost::asio::io_context& io_context_;
  std::thread io_thread_;
  std::unique_ptr<gui::GuiManager> gui_manager_;
  std::shared_ptr<SessionManager> session_manager_;
  std::shared_ptr<chat_lib::networking::Server> server_;
  std::shared_ptr<chat_lib::networking::Client> client_;
};
}  // namespace chat_exec::core

#endif  // P2P_CHAT_APP_APP_CORE_CHAT_CONTROLLER_H_