#include "gui/unavailable.h"

namespace chat_exec {

namespace gui {

Unavailable::Unavailable() : AbstractView("unavailable") {
  unavailable_widget_.setupUi(this);
}

QPushButton* Unavailable::get_OK_button() const {
  return unavailable_widget_.pushButton;
}

void Unavailable::somefunc() {}
}  // namespace gui
}  // namespace chat_exec
