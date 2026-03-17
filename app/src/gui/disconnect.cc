#include "gui/disconnect.h"

namespace chat_exec::gui {

Disconnect::Disconnect() : disconnect_widget_() {
  disconnect_widget_.setupUi(this);
  SetupConnections();
}

void Disconnect::SetupConnections() {
  connect(disconnect_widget_.ok_button, &QPushButton::clicked, this,
          &Disconnect::OKBttnClicked);
}
}  // namespace chat_exec::gui
