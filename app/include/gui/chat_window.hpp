#ifndef CHAT_WINDOW_HPP
#define CHAT_WINDOW_HPP

#include "ui/ui_chat_window.h"
#include "view.h"

namespace chat_exec {

namespace gui {

class ChatWindow : public AbstractView {
 public:
  ChatWindow();
  void somefunc() override;
  void display_message(std::string msg);
  [[nodiscard]] QString get_message() const;
  [[nodiscard]] QListWidget* get_chat_history() const;
  [[nodiscard]] QLineEdit* get_message_line_edit() const;
  [[nodiscard]] QPushButton* get_SEND_button() const;

  Ui::chat_window chat_window;
};
}  // namespace gui
}  // namespace chat_exec

#endif  // CHAT_WINDOW_HPP
