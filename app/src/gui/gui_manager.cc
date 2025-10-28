#include "gui/gui_manager.hpp"

#include <QPushButton>

GuiManager::GuiManager()
    : chat_window_(std::make_unique<ChatWindow>()),
        main_menu_(std::make_unique<MainMenu>()),
        unavailable_(std::make_unique<Unavailable>()),
        add_host_(std::make_unique<AddHost>())
{
    connect(main_menu_->get_add_host_button(), &QPushButton::clicked, this, &GuiManager::open_add_host);
    connect(add_host_->get_cancel_button(), &QPushButton::clicked, this, &GuiManager::go_back);
    connect(add_host_->get_add_button(), &QPushButton::clicked, this, &GuiManager::new_host_added);
    connect(main_menu_->get_connect_button(), &QPushButton::clicked, this, &GuiManager::chat_window_opened_wrapper);
    connect(unavailable_->get_OK_button(), &QPushButton::clicked, this, &GuiManager::go_back);
    // connect(main_menu_->get_client_button(), &QPushButton::clicked, this, &GuiManager::open_ip_port_prompt);
    // connect(main_menu_->get_server_button(), &QPushButton::clicked, this, &GuiManager::open_port_prompt);
    // connect(port_prompt_->get_OK_button(), &QPushButton::clicked, this, &GuiManager::open_server_listen_connection);
    // connect(port_prompt_->get_OK_button(), &QPushButton::clicked, this, &GuiManager::server_port_given);
    // connect(direct_connection_->get_OK_button(), &QPushButton::clicked, this, &GuiManager::client_ip_port_given);
    connect(chat_window_->get_SEND_button(), &QPushButton::clicked, this, &GuiManager::emit_sent_msg);
    // connect(program_mode_->program_mode.pushButton, &QPushButton::clicked, this, &GuiManager::open_prompt);
    // connect(program_mode_->program_mode.pushButton, &QPushButton::clicked, this, &GuiManager::open_prompt);
}

void GuiManager::chat_window_opened_wrapper() {
    emit chat_window_opened(get_host_ip());
}

void GuiManager::new_host_added() {
    auto new_host_name = add_host_->get_host_name();
    auto new_host_ip = add_host_->get_host_ip();
    main_menu_->add_new_host(new_host_name, new_host_ip);
    go_back();
}

std::string GuiManager::get_host_ip() const {
    return main_menu_->get_selected_host();
}

void GuiManager::go_into(AbstractView* dst) {
    if (!nav_stack_.empty()) nav_stack_.top()->hide();
    nav_stack_.push(dst);
    nav_stack_.top()->show();
}

void GuiManager::go_back() {
    if (!nav_stack_.empty()) {
        nav_stack_.top()->hide();
        nav_stack_.pop();
        nav_stack_.top()->show();
    }
}

void GuiManager::emit_sent_msg() {
    auto msg = chat_window_->get_message();
    emit message_sent(msg);
}

void GuiManager::display_received_msg(QString msg) {
    chat_window_->display_message(msg.toStdString());
}

void GuiManager::open_main_menu() {
    go_into(main_menu_.get());
}

void GuiManager::open_chat_window() {
    go_into(chat_window_.get());
}

void GuiManager::open_unavailable() {
    go_into(unavailable_.get());
}

void GuiManager::open_add_host() {
    go_into(add_host_.get());
}


