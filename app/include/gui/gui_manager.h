#ifndef P2P_CHAT_APP_GUI_GUI_MANAGER_H_
#define P2P_CHAT_APP_GUI_GUI_MANAGER_H_

#include <memory>
#include <stack>
#include <string>

#include "add_host.h"
#include "chat_window.h"
#include "gui/disconnect.h"
#include "gui/unavailable.h"
#include "main_menu.h"

namespace chat_exec::gui {

/// @brief Manages the application's user interface and navigation flow.
/**
 * This class owns all individual widget instances and controls
 * which one is currently displayed using a stack-based navigation history.
 *
 * It also serves as a forwarding hub for some signals coming from UI events,
 * which are supposed to be handled by slots located in application's core
 * Controller.
 */
class GuiManager : public QObject {
  Q_OBJECT
 public:
  GuiManager();
  [[nodiscard]] std::string GetHostIP() const;

  /// @brief Navigates to a specific widget, adding it to the navigation stack
  /// and displaying it.
  /**
   * @param dst Destination widget upon which @code .show()@endcode will be
   * called.
   */
  void GoInto(QWidget* dst);

  /**
   * @name Navigation Wrappers
   * Public slots which trigger navigation to specific views. These wrappers
   * provide encapsulation for the underlying widget pointers.
   */
 public slots:
  void OpenMainMenu();
  void OpenChatWindow();
  void OpenUnavailable();
  void OpenHostDisconnected();
  void OpenAddHost();
  void EmitSentMsg();
  void DisplayReceivedMsg(QString msg);
  void NewHostAdded();
  void GoBackToMenu();
  void GoBack();

  void ChatWindowOpenedWrapper();

 signals:
  void ChatWindowOpened(std::string target_ip);
  void MessageSent(QString msg);

 private:
  void SetupConnections();
  void SetupObjectNames();

  /// @brief Stack maintaining the history of visited widgets. Top is the
  /// currently visible widget
  std::stack<QWidget*> nav_stack_;

  std::unique_ptr<ChatWindow> chat_window_;
  std::unique_ptr<MainMenu> main_menu_;
  std::unique_ptr<Unavailable> unavailable_;
  std::unique_ptr<Disconnect> disconnect_;
  std::unique_ptr<AddHost> add_host_;
};

}  // namespace chat_exec::gui

#endif  // P2P_CHAT_APP_GUI_GUI_MANAGER_H_
