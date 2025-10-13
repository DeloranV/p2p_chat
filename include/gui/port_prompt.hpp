//
// Created by rolandgugalapwrrt on 17.10.25.
//

#ifndef PORT_PROMPT_HPP
#define PORT_PROMPT_HPP

#include "gui/view.h"
#include "ui/ui_port_prompt.h"

class PortPrompt : public AbstractView {
public:
    PortPrompt();
    void somefunc() override;
    std::string get_port() const;
    QLineEdit* get_port_line_edit() const;
    QPushButton* get_OK_button() const;

    Ui::port_prompt_widget port_prompt;
};

#endif //PORT_PROMPT_HPP
