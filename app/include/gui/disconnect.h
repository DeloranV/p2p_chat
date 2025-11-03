#ifndef CHAT_APP_DISCONNECT_H
#define CHAT_APP_DISCONNECT_H

#include "ui/ui_disconnect.h"
#include "view.h"

namespace chat_exec {

namespace gui {

class Disconnect : public AbstractView {
 public:
  Disconnect();
  void somefunc() override;
  [[nodiscard]] QPushButton* get_OK_button() const;

 private:
  Ui::disconnect_widget disconnect_widget_;
};
}  // namespace gui
}  // namespace chat_exec

#endif  // CHAT_APP_DISCONNECT_H