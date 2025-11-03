#ifndef CHAT_APP_PROGRAM_MODE_H
#define CHAT_APP_PROGRAM_MODE_H

#include "ui/ui_main_menu.h"
#include "view.h"

namespace chat_exec {

namespace gui {

class MainMenu : public AbstractView {
 public:
  MainMenu();
  [[nodiscard]] QPushButton* get_connect_button() const;
  [[nodiscard]] QListWidget* get_hosts_list() const;
  [[nodiscard]] std::string get_selected_host() const;
  [[nodiscard]] QPushButton* get_add_host_button() const;
  void add_new_host(std::string hostname, std::string ip_addr);
  void somefunc() override;

 private:
  Ui::main_menu_widget main_menu_widget_;
};
}  // namespace gui
}  // namespace chat_exec

#endif  // CHAT_APP_PROGRAM_MODE_H