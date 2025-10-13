//
// Created by rolandpwrrt on 13.10.2025.
//

#ifndef CHAT_APP_PROGRAM_MODE_H
#define CHAT_APP_PROGRAM_MODE_H

#include "gui/view.h"
#include "ui/ui_program_mode.h"

class ProgramMode : public AbstractView {
public:
  ProgramMode();
  QPushButton* get_server_button() const;
  QPushButton* get_client_button() const;
  void somefunc() override;
  Ui::program_mode_widget program_mode;
};

#endif //CHAT_APP_PROGRAM_MODE_H