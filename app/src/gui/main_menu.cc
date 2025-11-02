#include "gui/main_menu.h"

MainMenu::MainMenu()
  : AbstractView("main_menu")
{
  main_menu_widget_.setupUi(this);
}

void MainMenu::somefunc() {

}

void MainMenu::add_new_host(std::string hostname, std::string ip_addr) {
  auto host_display_name = hostname + "->" + ip_addr;
  new QListWidgetItem(QString(host_display_name.c_str()), get_hosts_list());
}

QPushButton* MainMenu::get_connect_button() const {
  return main_menu_widget_.pushButton;
}

QPushButton* MainMenu::get_add_host_button() const {
  return main_menu_widget_.pushButton_3;
}

QListWidget* MainMenu::get_hosts_list() const {
  return main_menu_widget_.listWidget;
}

std::string MainMenu::get_selected_host() const {
  auto fullname = get_hosts_list()->currentItem()->text().toStdString();
  return fullname.substr(fullname.rfind('>') + 1);
}

