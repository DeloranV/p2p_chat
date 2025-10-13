#include "gui/port_prompt.hpp"

PortPrompt::PortPrompt() {
    port_prompt.setupUi(this);
}

void PortPrompt::somefunc() {

}

QLineEdit* PortPrompt::get_port_line_edit() const {
    return port_prompt.lineEdit;
}

QPushButton* PortPrompt::get_OK_button() const {
    return port_prompt.pushButton;
}

std::string PortPrompt::get_port() const {
    return get_port_line_edit()->text().toStdString();
}


