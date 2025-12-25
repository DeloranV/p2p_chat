#include "gui/add_host.h"

namespace chat_exec::gui {
AddHost::AddHost() : add_host_widget_() {
  add_host_widget_.setupUi(this);
  setup_connections();
}

std::string AddHost::get_host_ip() const {
  return add_host_widget_.ip_line_edit->text().toStdString();
}

std::string AddHost::get_host_name() const {
  return add_host_widget_.host_name_line_edit->text().toStdString();
}

void AddHost::setup_connections() {
  connect(add_host_widget_.cancel_button, &QPushButton::clicked, this,
          &AddHost::cancel_bttn_clicked);
  connect(add_host_widget_.add_button, &QPushButton::clicked, this,
          &AddHost::add_bttn_clicked);
}
}  // namespace chat_exec::gui