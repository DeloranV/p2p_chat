//
// Created by rolandpwrrt on 28.10.2025.
//

#ifndef CHAT_APP_ADD_HOST_H
#define CHAT_APP_ADD_HOST_H

#include "view.h"
#include "ui/ui_add_host.h"

class AddHost : public AbstractView {
public:
  AddHost();
  void somefunc() override;
  QPushButton* get_cancel_button() const;
  QPushButton* get_add_button() const;
  QLineEdit* get_ip_line_edit() const;
  QLineEdit* get_host_name_line_edit() const;
  std::string get_host_ip() const;
  std::string get_host_name() const;

private:
  Ui::add_host_widget add_host_widget_;
};

#endif //CHAT_APP_ADD_HOST_H