#include "gui/unavailable.h"

namespace chat_exec::gui {

Unavailable::Unavailable() : unavailable_widget_() {
  unavailable_widget_.setupUi(this);
  SetupConnected();
}

void Unavailable::SetupConnected() {
  connect(unavailable_widget_.ok_button, &QPushButton::clicked, this,
          &Unavailable::OKBttnClicked);
}
}  // namespace chat_exec::gui