#ifndef CHAT_APP_ADD_HOST_H
#define CHAT_APP_ADD_HOST_H

#include "ui/ui_add_host.h"

namespace chat_exec::gui {

/// @brief Widget for adding a new host to the main menu selection.
class AddHost : public QWidget {
  Q_OBJECT
 public:
  AddHost();

  /// @brief Returns the entered host IP
  [[nodiscard]] std::string get_host_ip() const;

  /// @brief Returns the entered hostname
  [[nodiscard]] std::string get_host_name() const;

  Ui::add_host_widget add_host_widget_;

 signals:
  void cancel_bttn_clicked();
  void add_bttn_clicked();

 private:
  void setup_connections();
};
}  // namespace chat_exec::gui

#endif  // CHAT_APP_ADD_HOST_H