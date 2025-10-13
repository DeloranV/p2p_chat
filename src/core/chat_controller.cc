//
// Created by rolandpwrrt on 7.10.2025.
//

#include "core/chat_controller.h"
#include "gui/program_mode.h"
#include "gui/view.h"
#include "core/session_adapter.h"

  ChatController::ChatController(boost::asio::io_context& io_context)
    : io_context_(io_context),
      gui_manager_(std::make_unique<GuiManager>()),
      adapter_(std::make_shared<SessionAdapter>(io_context))
  {
    connect(gui_manager_.get(), &GuiManager::server_port_given, this, &ChatController::start_server);
    connect(this, &ChatController::client_connected, gui_manager_.get(), &GuiManager::open_chat_window);
    connect(gui_manager_.get(), &GuiManager::client_ip_port_given, this, &ChatController::start_client);
    connect(gui_manager_.get(), &GuiManager::message_sent, adapter_.get(), &SessionAdapter::message_sent);
    connect(adapter_.get(), &SessionAdapter::message_received, gui_manager_.get(), &GuiManager::display_received_msg);
  }

  void ChatController::run() {
    gui_manager_->open_program_mode();
  }

  void ChatController::start_client() {
    chat_thread_ = boost::thread([this] {
      auto port = gui_manager_->getIpPortPrompt().get_port();
      auto ip = gui_manager_->getIpPortPrompt().get_ip();
      client_ = std::make_shared<networking::Client>(io_context_);
      session_ = client_->create_session(ip, port, *adapter_);
      adapter_->register_session(session_);
      emit client_connected();

      session_->listen_msg();
      //
      // cli_manager_->await_input(
      //   std::bind(&session::chat_session::send_msg, session_, std::placeholders::_1));
      io_context_.run();
    });
  }

  void ChatController::start_server() {
    chat_thread_ = boost::thread([this] {
      auto port = gui_manager_->getPortPrompt().get_port();
      server_ = std::make_shared<networking::Server>(io_context_, port);
      session_ = server_->await_connection(*adapter_);
      adapter_->register_session(session_);
      emit client_connected();

      session_->listen_msg();

    // cli_manager_->await_input(
    //   std::bind(&session::chat_session::send_msg, session_, std::placeholders::_1));
      io_context_.run();
    });
  }
