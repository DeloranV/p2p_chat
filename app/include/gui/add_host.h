#ifndef P2P_CHAT_APP_GUI_ADD_HOST_H_
#define P2P_CHAT_APP_GUI_ADD_HOST_H_

#include "ui/ui_add_host.h"

namespace chat_exec::gui {

/// @brief Widget for adding a new host to the main menu selection.
class AddHost : public QWidget {
  Q_OBJECT
 public:
  AddHost();

  /// @brief Returns the entered host IP
  [[nodiscard]] std::string GetHostIP() const;

  /// @brief Returns the entered hostname
  [[nodiscard]] std::string GetHostName() const;

  Ui::add_host_widget add_host_widget_;

 signals:
  void CancelBttnClicked();
  void AddBttnClicked();

 private:
  void SetupConnections();
};
}  // namespace chat_exec::gui

#endif  // P2P_CHAT_APP_GUI_ADD_HOST_H_