#include "gui/gui_manager.hpp"

#include <QPushButton>

GuiManager::GuiManager()
    : chat_window_(std::make_unique<ChatWindow>()),
        ip_port_prompt_(std::make_unique<IpPortPrompt>()),
        port_prompt_(std::make_unique<PortPrompt>()),
        program_mode_(std::make_unique<ProgramMode>()),
        server_listen_connection_(std::make_unique<ServerListenConnection>())
{
    connect(program_mode_->get_client_button(), &QPushButton::clicked, this, &GuiManager::open_ip_port_prompt);
    connect(program_mode_->get_server_button(), &QPushButton::clicked, this, &GuiManager::open_port_prompt);
    connect(port_prompt_->get_OK_button(), &QPushButton::clicked, this, &GuiManager::open_server_listen_connection);
    connect(port_prompt_->get_OK_button(), &QPushButton::clicked, this, &GuiManager::server_port_given);
    connect(ip_port_prompt_->get_OK_button(), &QPushButton::clicked, this, &GuiManager::client_ip_port_given);
    connect(chat_window_->get_SEND_button(), &QPushButton::clicked, this, &GuiManager::emit_sent_msg);
    // connect(program_mode_->program_mode.pushButton, &QPushButton::clicked, this, &GuiManager::open_prompt);
    // connect(program_mode_->program_mode.pushButton, &QPushButton::clicked, this, &GuiManager::open_prompt);
}

void GuiManager::go_into(AbstractView* dst) {
    if (!nav_stack_.empty()) nav_stack_.top()->hide();
    nav_stack_.push(dst);
    nav_stack_.top()->show();
}

PortPrompt& GuiManager::getPortPrompt() const {
    return *port_prompt_;
}

IpPortPrompt& GuiManager::getIpPortPrompt() const {
    return *ip_port_prompt_;
}

void GuiManager::emit_sent_msg() {
    auto msg = chat_window_->get_message();
    emit message_sent(msg);
}

void GuiManager::display_received_msg(QString msg) {
    chat_window_->display_message(msg.toStdString());
}

void GuiManager::open_program_mode() {
    go_into(program_mode_.get());
}

void GuiManager::open_port_prompt() {
    go_into(port_prompt_.get());
}

void GuiManager::open_chat_window() {
    go_into(chat_window_.get());
}

void GuiManager::open_ip_port_prompt() {
    go_into(ip_port_prompt_.get());
}

void GuiManager::open_server_listen_connection() {
    go_into(server_listen_connection_.get());
}


