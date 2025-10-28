//
// Created by rolandpwrrt on 13.10.2025.
//

#ifndef CHAT_APP_PROGRAM_MODE_H
#define CHAT_APP_PROGRAM_MODE_H

#include "view.h"
#include "ui/ui_main_menu.h"

class MainMenu : public AbstractView {
public:
  MainMenu();
  QPushButton* get_connect_button() const;
  QListWidget* get_hosts_list() const;
  std::string get_selected_host() const;
  QPushButton* get_add_host_button() const;
  void add_new_host(std::string hostname, std::string ip_addr);
  void somefunc() override;

private:
  Ui::main_menu_widget main_menu_widget_;
};

#endif //CHAT_APP_PROGRAM_MODE_H