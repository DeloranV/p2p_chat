#include "gui/gui_manager.h"

#include "network/client.h"

namespace chat_exec::gui {

GuiManager::GuiManager()
    : chat_window_(std::make_unique<ChatWindow>()),
      main_menu_(std::make_unique<MainMenu>()),
      unavailable_(std::make_unique<Unavailable>()),
      add_host_(std::make_unique<AddHost>()),
      disconnect_(std::make_unique<Disconnect>()) {
  SetupConnections();
  SetupObjectNames();
  OpenMainMenu();
}

void GuiManager::SetupConnections() {
  connect(main_menu_.get(), &MainMenu::AddHostBttnClicked, this,
          &GuiManager::OpenAddHost);
  connect(add_host_.get(), &AddHost::CancelBttnClicked, this,
          &GuiManager::GoBack);
  connect(add_host_.get(), &AddHost::AddBttnClicked, this,
          &GuiManager::NewHostAdded);
  connect(main_menu_.get(), &MainMenu::ConnectBttnClicked, this,
          &GuiManager::ChatWindowOpenedWrapper);
  connect(unavailable_.get(), &Unavailable::OKBttnClicked, this,
          &GuiManager::GoBack);
  connect(disconnect_.get(), &Disconnect::OKBttnClicked, this,
          &GuiManager::GoBackToMenu);
  connect(chat_window_.get(), &ChatWindow::SendBttnClicked, this,
          &GuiManager::EmitSentMsg);
}

void GuiManager::SetupObjectNames() {
  main_menu_->setObjectName("main_menu");
  add_host_->setObjectName("add_host");
  chat_window_->setObjectName("chat_window");
  unavailable_->setObjectName("unavailable");
  disconnect_->setObjectName("disconnect");
}

void GuiManager::ChatWindowOpenedWrapper() {
  emit ChatWindowOpened(GetHostIP());
}

void GuiManager::NewHostAdded() {
  auto new_host_name = add_host_->GetHostName();
  auto new_host_ip = add_host_->GetHostIP();
  main_menu_->AddNewHost(new_host_name, new_host_ip);
  GoBack();
}

std::string GuiManager::GetHostIP() const {
  return main_menu_->GetSelectedHost();
}

void GuiManager::GoInto(QWidget* dst) {
  if (!nav_stack_.empty()) nav_stack_.top()->hide();
  nav_stack_.push(dst);
  nav_stack_.top()->show();
}

void GuiManager::GoBack() {
  if (nav_stack_.size() > 1) {
    nav_stack_.top()->hide();
    nav_stack_.pop();
    nav_stack_.top()->show();
  }
}

void GuiManager::GoBackToMenu() {
  if (!nav_stack_.empty()) {
    nav_stack_.top()->hide();
    while (nav_stack_.size() > 1 &&
           nav_stack_.top()->objectName() != "main_menu")
      nav_stack_.pop();
    nav_stack_.top()->show();
  }
}

void GuiManager::EmitSentMsg() {
  auto msg = chat_window_->GetMessage();
  emit MessageSent(msg);
}

void GuiManager::DisplayReceivedMsg(QString msg) {
  chat_window_->DisplayMessage(msg.toStdString());
}

void GuiManager::OpenMainMenu() { GoInto(main_menu_.get()); }
void GuiManager::OpenChatWindow() { GoInto(chat_window_.get()); }
void GuiManager::OpenUnavailable() { GoInto(unavailable_.get()); }
void GuiManager::OpenAddHost() { GoInto(add_host_.get()); }
void GuiManager::OpenHostDisconnected() { GoInto(disconnect_.get()); }
}  // namespace chat_exec::gui
