//
// Created by rolandpwrrt on 17.10.2025.
//

#ifndef CHAT_APP_VIEW_H
#define CHAT_APP_VIEW_H

#include <QtWidgets/QWidget>
#include <QObject>

class AbstractView : public QWidget {
  Q_OBJECT
public:
  AbstractView(std::string name)
    : view_name(std::move(name))
  {}

  virtual void somefunc() = 0;

  const std::string view_name;
};

#endif //CHAT_APP_VIEW_H