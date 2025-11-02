//
// Created by rolandpwrrt on 28.10.2025.
//

#ifndef CHAT_APP_DISCONNECT_H
#define CHAT_APP_DISCONNECT_H

#include "view.h"
#include "ui/ui_disconnect.h"

class Disconnect : public AbstractView {
public:
  Disconnect();
  void somefunc() override;
  QPushButton* get_OK_button() const;

private:
  Ui::disconnect_widget disconnect_widget_;
};

#endif //CHAT_APP_DISCONNECT_H