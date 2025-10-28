//
// Created by rolandpwrrt on 7.10.2025.
//

#include "app_core/chat_controller.h"
#include "gui/main_menu.h"
#include "gui/view.h"
#include "app_core/session_adapter.h"

ChatController::ChatController(boost::asio::io_context &io_context)
  : io_context_(io_context),
    gui_manager_(std::make_unique<GuiManager>()),
    adapter_(std::make_shared<SessionAdapter>(io_context)),
    session_manager_(std::make_shared<SessionManager>(io_context, adapter_)),
    server_(std::make_unique<networking::Server>(io_context)),
    client_(std::make_unique<networking::Client>(io_context)) {
  connect(gui_manager_.get(), &GuiManager::chat_window_opened, this, &ChatController::open_chat);
  connect(gui_manager_.get(), &GuiManager::message_sent, adapter_.get(), &SessionAdapter::message_sent);
  connect(adapter_.get(), &SessionAdapter::message_received, gui_manager_.get(), &GuiManager::display_received_msg);
}

void ChatController::run() {
  gui_manager_->open_main_menu();
  start_server();
}
// TODO timeout when trying to connect to an offline host
void ChatController::open_chat(std::string target_ip) {
  if (session_manager_->is_session_active(target_ip)) {
    gui_manager_->open_chat_window();
    return;
  }
  try {
    auto host_ip = gui_manager_->get_host_ip();
    auto s_socket = client_->try_connect(host_ip);
    // std::move SINCE WE NEED TO TRANSFER OWNERSHIP OF THE SOCKET TO THE SESSION
    session_manager_->start_session(std::move(s_socket), *adapter_);
    start_client();
  } catch (boost::system::system_error &err) {
    gui_manager_->open_unavailable();
  }
}

void ChatController::start_client() {
  gui_manager_->open_chat_window();
  client_thread_ = boost::thread([this] {
    io_context_.run();
  });
}

void ChatController::start_server() {
  server_thread_ = boost::thread([this] {
    server_->await_connection([this](ssl_socket s) {
      session_manager_->start_session(std::move(s), *adapter_);
    });
    io_context_.run();
  });
}

ChatController::~ChatController() {
  io_context_.stop();
}
