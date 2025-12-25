#include "gui/unavailable.h"

namespace chat_exec::gui {

Unavailable::Unavailable() : unavailable_widget_() {
  unavailable_widget_.setupUi(this);
  setup_connections();
}

void Unavailable::setup_connections() {
  connect(unavailable_widget_.ok_button, &QPushButton::clicked, this,
          &Unavailable::ok_bttn_clicked);
}
}  // namespace chat_exec::gui