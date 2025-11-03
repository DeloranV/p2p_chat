#ifndef CHAT_APP_UNAVAILABLE_H
#define CHAT_APP_UNAVAILABLE_H

#include "ui/ui_unavailable.h"
#include "view.h"

namespace chat_exec {

namespace gui {

class Unavailable : public AbstractView {
 public:
  Unavailable();
  void somefunc() override;
  [[nodiscard]] QPushButton* get_OK_button() const;

 private:
  Ui::unavailable_widget unavailable_widget_;
};
}  // namespace gui
}  // namespace chat_exec

#endif  // CHAT_APP_UNAVAILABLE_H