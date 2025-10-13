#include "gui/program_mode.h"

ProgramMode::ProgramMode() {
  program_mode.setupUi(this);
}

void ProgramMode::somefunc() {

}

QPushButton* ProgramMode::get_server_button() const {
  return program_mode.pushButton;
}

QPushButton* ProgramMode::get_client_button() const {
  return program_mode.pushButton_2;
}


