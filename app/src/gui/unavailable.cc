#include "gui/unavailable.h"

Unavailable::Unavailable() {
  unavailable_widget_.setupUi(this);
}

QPushButton* Unavailable::get_OK_button() const {
  return unavailable_widget_.pushButton;
}


void Unavailable::somefunc() {

}

