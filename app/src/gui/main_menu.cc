#include "gui/main_menu.h"

#include <iostream>

namespace chat_exec::gui {

MainMenu::MainMenu() : main_menu_widget_() {
  main_menu_widget_.setupUi(this);
  setup_connections();

  // (TODO) These are for development purposes only - no way to bake-in in Qt
  // Designer
  if (main_menu_widget_.hosts_list->count() > 0) {
    main_menu_widget_.hosts_list->item(0)->setData(
        Qt::UserRole, QString::fromStdString("192.168.0.17"));
  }
  if (main_menu_widget_.hosts_list->count() > 1) {
    main_menu_widget_.hosts_list->item(1)->setData(
        Qt::UserRole, QString::fromStdString("192.168.0.23"));
  }
}

void MainMenu::add_new_host(std::string hostname, std::string ip_addr) {
  auto host_display_name = hostname + "->" + ip_addr;
  auto added_host =  // Might show a leaked memory warning - it has the
                     // hosts_list as parent so Qt cleans it up
      new QListWidgetItem(QString::fromStdString(host_display_name),
                          main_menu_widget_.hosts_list);
  added_host->setData(Qt::UserRole, QString::fromStdString(ip_addr));
}

std::string MainMenu::get_selected_host() const {
  auto selected_item = main_menu_widget_.hosts_list->currentItem();
  if (selected_item == nullptr) return "";

  auto ip_addr = selected_item->data(Qt::UserRole).toString().toStdString();
  return ip_addr;
}

void MainMenu::setup_connections() {
  connect(main_menu_widget_.add_host_button, &QPushButton::clicked, this,
          &MainMenu::add_host_bttn_clicked);
  connect(main_menu_widget_.connect_button, &QPushButton::clicked, this,
          &MainMenu::connect_bttn_clicked);
}
}  // namespace chat_exec::gui
