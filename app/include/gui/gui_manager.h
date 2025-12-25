#ifndef GUI_MANAGER_HPP
#define GUI_MANAGER_HPP

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
  [[nodiscard]] std::string get_host_ip() const;

  /// @brief Navigates to a specific widget, adding it to the navigation stack
  /// and displaying it.
  /**
   * @param dst Destination widget upon which @code .show()@endcode will be
   * called.
   */
  void go_into(QWidget* dst);

  /**
   * @name Navigation Wrappers
   * Public slots which trigger navigation to specific views. These wrappers
   * provide encapsulation for the underlying widget pointers.
   */
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
  void setup_connections();
  void setup_object_names();

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

#endif  // GUI_MANAGER_HPP
