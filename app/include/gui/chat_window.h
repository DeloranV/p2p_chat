#ifndef CHAT_WINDOW_HPP
#define CHAT_WINDOW_HPP

#include "ui/ui_chat_window.h"

namespace chat_exec::gui {

/// @brief Widget displaying an open chat window.
/**
 * The message history is implemented as a @code QListWidget@endcode, which
 * gets appended with @code QListWidgetItem@endcode containing message contents
 * and metadata.
 */
class ChatWindow : public QWidget {
  Q_OBJECT
 public:
  ChatWindow();

  /// @brief Displays a message in the chat window by appending a new
  /// @code QListWidgetItem@endcode holding its contents.
  /**
   * @param msg A deserialized and properly formatted string to be displayed
   * in the message history.
   */
  void display_message(std::string msg);  // (TODO) See util.h in core_lib

  /// @brief Returns the message string which was typed into the textbox.
  [[nodiscard]] QString get_message() const;

  Ui::chat_window chat_window;

 signals:
  void send_bttn_clicked();

 private:
  void setup_connections();
};
}  // namespace chat_exec::gui

#endif  // CHAT_WINDOW_HPP
