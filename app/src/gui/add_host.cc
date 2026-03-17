#include "gui/add_host.h"

namespace chat_exec::gui {
AddHost::AddHost() : add_host_widget_() {
  add_host_widget_.setupUi(this);
  SetupConnections();
}

std::string AddHost::GetHostIP() const {
  return add_host_widget_.ip_line_edit->text().toStdString();
}

std::string AddHost::GetHostName() const {
  return add_host_widget_.host_name_line_edit->text().toStdString();
}

void AddHost::SetupConnections() {
  connect(add_host_widget_.cancel_button, &QPushButton::clicked, this,
          &AddHost::CancelBttnClicked);
  connect(add_host_widget_.add_button, &QPushButton::clicked, this,
          &AddHost::AddBttnClicked);
}
}  // namespace chat_exec::gui