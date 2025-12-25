#include "gui/disconnect.h"

namespace chat_exec::gui {

Disconnect::Disconnect() : disconnect_widget_() {
  disconnect_widget_.setupUi(this);
  setup_connections();
}

void Disconnect::setup_connections() {
  connect(disconnect_widget_.ok_button, &QPushButton::clicked, this,
          &Disconnect::ok_bttn_clicked);
}
}  // namespace chat_exec::gui
