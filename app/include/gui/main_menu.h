#ifndef P2P_CHAT_APP_GUI_MAIN_MENU_H_
#define P2P_CHAT_APP_GUI_MAIN_MENU_H_

#include "ui/ui_main_menu.h"

namespace chat_exec::gui {

/// @brief Widget displaying the main menu of the program.
/**
 * Main menu consists of a known-hosts list, a button to append a new host
 * to the list and a button to start a chat session with the selected host.
 */
class MainMenu : public QWidget {
  Q_OBJECT
 public:
  MainMenu();

  /// @brief Returns the IP address of a selected host from the list.
  /**
   * @return IP address of the selected host in the form of a string.
   */
  [[nodiscard]] std::string GetSelectedHost() const;

  /// @brief Adds a new host to the list.
  /**
   * @param hostname A nickname given to the added host.
   * @param ip_addr The IP address of the added host.
   */
  void AddNewHost(std::string hostname, std::string ip_addr);

  Ui::main_menu_widget main_menu_widget_;

 signals:
  void AddHostBttnClicked();
  void ConnectBttnClicked();

 private:
  void SetupConnections();
};
}  // namespace chat_exec::gui

#endif  // P2P_CHAT_APP_GUI_MAIN_MENU_H_