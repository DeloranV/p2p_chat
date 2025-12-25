#ifndef CHAT_APP_UNAVAILABLE_H
#define CHAT_APP_UNAVAILABLE_H

#include "ui/ui_unavailable.h"

namespace chat_exec::gui {

/// @brief Widget displaying a 'host unavailable' message with an 'OK' button.
class Unavailable : public QWidget {
  Q_OBJECT
 public:
  Unavailable();

  Ui::unavailable_widget unavailable_widget_;

 signals:
  void ok_bttn_clicked();

 private:
  void setup_connections();
};
}  // namespace chat_exec::gui

#endif  // CHAT_APP_UNAVAILABLE_H