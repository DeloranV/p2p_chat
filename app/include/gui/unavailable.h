//
// Created by rolandpwrrt on 28.10.2025.
//

#ifndef CHAT_APP_UNAVAILABLE_H
#define CHAT_APP_UNAVAILABLE_H

#include "view.h"
#include "ui/ui_unavailable.h"

class Unavailable : public AbstractView {
public:
  Unavailable();
  void somefunc() override;
  QPushButton* get_OK_button() const;

private:
  Ui::unavailable_widget unavailable_widget_;
};

#endif //CHAT_APP_UNAVAILABLE_H