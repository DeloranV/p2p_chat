#ifndef GUI_MANAGER_HPP
#define GUI_MANAGER_HPP

#include <memory>
#include <stack>
#include <string>
// TODO MOVE THESE INCLUDES TO A SINGLE .H FILE ui/ui_elements.h AND INCLUDE
// THAT
#include "add_host.h"
#include "chat_window.hpp"
#include "gui/disconnect.h"
#include "gui/unavailable.h"
#include "main_menu.h"
#include "view.h"

namespace chat_exec {

namespace gui {

class GuiManager : public QObject {
  Q_OBJECT
 public:
  GuiManager();
  [[nodiscard]] std::string get_host_ip() const;
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
  std::stack<AbstractView*>
      nav_stack_;  // TODO CHANE UNIQUEPTR TO THE QT PARENT CHILD OWNERSHIP ?
  std::unique_ptr<ChatWindow> chat_window_;
  std::unique_ptr<MainMenu> main_menu_;
  std::unique_ptr<Unavailable> unavailable_;
  std::unique_ptr<Disconnect> disconnect_;
  std::unique_ptr<AddHost> add_host_;
};

}  // namespace gui
}  // namespace chat_exec

#endif  // GUI_MANAGER_HPP
