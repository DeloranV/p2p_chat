#ifndef P2P_CHAT_APP_GUI_DISCONNECT_H_
#define P2P_CHAT_APP_GUI_DISCONNECT_H_

#include "ui/ui_disconnect.h"

namespace chat_exec::gui {

///@brief Widget displaying a 'host disconnected' message with an 'OK' button.
class Disconnect : public QWidget {
  Q_OBJECT
 public:
  Disconnect();

  Ui::disconnect_widget disconnect_widget_;

 signals:
  void OKBttnClicked();

 private:
  void SetupConnections();
};
}  // namespace chat_exec::gui

#endif  // P2P_CHAT_APP_GUI_DISCONNECT_H_