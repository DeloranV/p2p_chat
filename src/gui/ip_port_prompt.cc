#include "gui/ip_port_prompt.hpp"

IpPortPrompt::IpPortPrompt() {
    ip_port_prompt.setupUi(this);
}

void IpPortPrompt::somefunc() {

}

QLineEdit* IpPortPrompt::get_ip_line_edit() const {
    return ip_port_prompt.lineEdit;
}

QLineEdit* IpPortPrompt::get_port_line_edit() const {
    return ip_port_prompt.lineEdit_2;
}

QPushButton* IpPortPrompt::get_OK_button() const {
    return ip_port_prompt.pushButton;
}

std::string IpPortPrompt::get_ip() const {
    return get_ip_line_edit()->text().toStdString();
}

std::string IpPortPrompt::get_port() const {
    return get_port_line_edit()->text().toStdString();
}
