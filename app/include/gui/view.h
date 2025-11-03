#ifndef CHAT_APP_VIEW_H
#define CHAT_APP_VIEW_H

#include <QtWidgets/QWidget>

namespace chat_exec {

namespace gui {

class AbstractView : public QWidget {
  Q_OBJECT
 public:
  explicit AbstractView(std::string name) : view_name(std::move(name)) {}

  virtual void somefunc() = 0;

  const std::string view_name;
};
}  // namespace gui
}  // namespace chat_exec

#endif  // CHAT_APP_VIEW_H