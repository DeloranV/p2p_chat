#ifndef CHAT_APP_ADD_HOST_H
#define CHAT_APP_ADD_HOST_H

#include "ui/ui_add_host.h"
#include "view.h"

namespace chat_exec {

namespace gui {

class AddHost : public AbstractView {
 public:
  AddHost();
  void somefunc() override;
  [[nodiscard]] QPushButton* get_cancel_button() const;
  [[nodiscard]] QPushButton* get_add_button() const;
  [[nodiscard]] QLineEdit* get_ip_line_edit() const;
  [[nodiscard]] QLineEdit* get_host_name_line_edit() const;
  [[nodiscard]] std::string get_host_ip() const;
  [[nodiscard]] std::string get_host_name() const;

 private:
  Ui::add_host_widget add_host_widget_;
};
}  // namespace gui
}  // namespace chat_exec

#endif  // CHAT_APP_ADD_HOST_H