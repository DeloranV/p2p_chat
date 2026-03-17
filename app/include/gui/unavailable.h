#ifndef P2P_CHAT_APP_GUI_UNAVAILABLE_H_
#define P2P_CHAT_APP_GUI_UNAVAILABLE_H_

#include "ui/ui_unavailable.h"

namespace chat_exec::gui {

/// @brief Widget displaying a 'host unavailable' message with an 'OK' button.
class Unavailable : public QWidget {
  Q_OBJECT
 public:
  Unavailable();

  Ui::unavailable_widget unavailable_widget_;

 signals:
  void OKBttnClicked();

 private:
  void SetupConnected();
};
}  // namespace chat_exec::gui

#endif  // P2P_CHAT_APP_GUI_UNAVAILABLE_H_