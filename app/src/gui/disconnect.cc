#include "gui/disconnect.h"

namespace chat_exec {

namespace gui {

Disconnect::Disconnect() : AbstractView("disconnect") {
  disconnect_widget_.setupUi(this);
}

QPushButton* Disconnect::get_OK_button() const {
  return disconnect_widget_.pushButton;
}

void Disconnect::somefunc() {}

}  // namespace gui
}  // namespace chat_exec
