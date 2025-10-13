//
// Created by rolandgugalapwrrt on 17.10.25.
//

#ifndef IP_PORT_PROMPT_HPP
#define IP_PORT_PROMPT_HPP

#include "gui/view.h"
#include "ui/ui_ip_port_prompt.h"

class IpPortPrompt : public AbstractView {
public:
    IpPortPrompt();
    void somefunc() override;
    std::string get_ip() const;
    std::string get_port() const;
    QLineEdit* get_ip_line_edit() const;
    QLineEdit* get_port_line_edit() const;
    QPushButton* get_OK_button() const;

    Ui::ip_port_prompt_widget ip_port_prompt;
};

#endif //IP_PORT_PROMPT_HPP
