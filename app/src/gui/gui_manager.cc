#include "gui/gui_manager.hpp"

#include <QPushButton>

GuiManager::GuiManager()
    : chat_window_(std::make_unique<ChatWindow>()),
        main_menu_(std::make_unique<MainMenu>()),
        unavailable_(std::make_unique<Unavailable>()),
        add_host_(std::make_unique<AddHost>()),
        disconnect_(std::make_unique<Disconnect>())
{
    connect(main_menu_->get_add_host_button(), &QPushButton::clicked, this, &GuiManager::open_add_host);
    connect(add_host_->get_cancel_button(), &QPushButton::clicked, this, &GuiManager::go_back);
    connect(add_host_->get_add_button(), &QPushButton::clicked, this, &GuiManager::new_host_added);
    connect(main_menu_->get_connect_button(), &QPushButton::clicked, this, &GuiManager::chat_window_opened_wrapper);
    connect(unavailable_->get_OK_button(), &QPushButton::clicked, this, &GuiManager::go_back);
    connect(disconnect_->get_OK_button(), &QPushButton::clicked, this, &GuiManager::go_back_to_menu);
    connect(chat_window_->get_SEND_button(), &QPushButton::clicked, this, &GuiManager::emit_sent_msg);
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

void GuiManager::go_back_to_menu() {
    if (!nav_stack_.empty()) {
        nav_stack_.top()->hide();
        while (nav_stack_.top()->view_name != "main_menu") nav_stack_.pop();
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

void GuiManager::open_host_disconnected() {
    go_into(disconnect_.get());
}
