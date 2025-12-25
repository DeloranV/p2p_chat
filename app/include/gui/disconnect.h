#ifndef CHAT_APP_DISCONNECT_H
#define CHAT_APP_DISCONNECT_H

#include "ui/ui_disconnect.h"

namespace chat_exec::gui {

///@brief Widget displaying a 'host disconnected' message with an 'OK' button.
class Disconnect : public QWidget {
  Q_OBJECT
 public:
  Disconnect();

  Ui::disconnect_widget disconnect_widget_;

 signals:
  void ok_bttn_clicked();

 private:
  void setup_connections();
};
}  // namespace chat_exec::gui

#endif  // CHAT_APP_DISCONNECT_H