#include "gui/add_host.h"

AddHost::AddHost()
  : AbstractView("add_host")
{
  add_host_widget_.setupUi(this);
}

QPushButton* AddHost::get_add_button() const {
  return add_host_widget_.pushButton;
}

QPushButton *AddHost::get_cancel_button() const {
 return add_host_widget_.pushButton_2;
}

QLineEdit* AddHost::get_ip_line_edit() const {
  return add_host_widget_.lineEdit_2;
}

QLineEdit* AddHost::get_host_name_line_edit() const {
  return add_host_widget_.lineEdit;
}

std::string AddHost::get_host_ip() const {
  return get_ip_line_edit()->text().toStdString();
}

std::string AddHost::get_host_name() const {
  return get_host_name_line_edit()->text().toStdString();
}


void AddHost::somefunc() {

}

