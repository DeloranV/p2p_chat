#include "app_core/chat_controller.h"

namespace chat_exec::core {

ChatController::ChatController(boost::asio::io_context &io_context)
    : io_context_(io_context),
      gui_manager_(std::make_unique<gui::GuiManager>()),
      session_manager_(std::make_shared<SessionManager>(io_context)),
      server_(std::make_shared<chat_lib::networking::Server>(io_context)),
      client_(std::make_shared<chat_lib::networking::Client>(io_context)) {
  connect(gui_manager_.get(), &gui::GuiManager::chat_window_opened, this,
          &ChatController::open_chat);
  connect(gui_manager_.get(), &gui::GuiManager::message_sent,
          session_manager_.get(), &SessionManager::message_sent);
  connect(session_manager_.get(), &SessionManager::message_received,
          gui_manager_.get(), &gui::GuiManager::display_received_msg);
  connect(session_manager_.get(), &SessionManager::host_disconnect,
          gui_manager_.get(), &gui::GuiManager::open_host_disconnected);
}

void ChatController::run() {
  setup_server();
  start_io_context();
}

void ChatController::start_io_context() {
  if (io_thread_.joinable()) return;
  io_thread_ = std::thread([this] {
    auto work_guard = boost::asio::make_work_guard(io_context_);
    io_context_.run();
  });
}

void ChatController::open_chat(const std::string &target_ip) {
  if (session_manager_->is_session_active(target_ip)) {
    gui_manager_->open_chat_window();
    return;
  }
  try {
    auto host_ip = gui_manager_->get_host_ip();
    // (TODO #4) Remake client to be async
    auto s_socket = client_->try_connect(host_ip);
    session_manager_->start_session(std::move(s_socket));
    start_client();
  } catch (...) {
    gui_manager_->open_unavailable();
  }
}

void ChatController::start_client() { gui_manager_->open_chat_window(); }

void ChatController::setup_server() {
  server_->await_connection([this](chat_lib::session::ssl_socket s) {
    session_manager_->start_session(std::move(s));
  });
}

ChatController::~ChatController() {
  io_context_.stop();
  if (io_thread_.joinable()) io_thread_.join();
}
}  // namespace chat_exec::core

/*
=========================================================================
LEARNING NOTES & IMPLEMENTATION DETAILS (For Future Reference)
=========================================================================

  [Sharing resources between threads]
  SessionManager class is initially created by the main thread, and is being
  held by the ChatController. In setup_server, we call await_connection which
  enqueues a connection await operation along with a callback (calling
  start_session()) on the io_context queue, which will then be executed by our
  io_thread. There is no problem with the io_thread accessing this
  SessionManager member functions, since we pass *this in the lambda, so
  essentially the thread just receives the address of where it should jump to
  find this manager class. We can share resources between threads freely this
  way, since it's just passing a memory address of a resource, but we need to
  keep in mind proper synchronization and lifetime of shared resources.
  That's why it might be safer to share between threads heap-allocated objects
  (like our SessionManager) instead of stack-allocated, since another thread
  could try to access an object that went out of scope and was destroyed.

  [Joining different threads]
  We check whether a thread is joinable in the destructor, to perform
  cleanup by joining the io_thread to the main thread as soon as it has finished
  all outstanding work from running the io_context queue. But before doing that,
  we need to ensure that the io_context event loop stops. Since we used the
  work_guard to make sure that the event loop keeps going even if there are
  no tasks in the io_context queue, we need to call .stop() in order to have
  the .run() (being executed by the thread) return as soon as possible.

  In start_io_context() we need to first check whether out io_context thread
  is joinable - if it is then that means it is most likely already running.
  If then we tried to yet again assign a std::thread with a lambda, it would
  cause the previous running thread to detach and crash the program.

*/