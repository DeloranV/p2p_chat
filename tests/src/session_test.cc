#include "chat_core/session.h"

#include <gtest/gtest.h>

#include <chrono>
#include <future>

#include "boost/asio.hpp"
#include "network/client.h"
#include "network/server.h"
#include "util/message.pb.h"
#include "util/util.h"

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> ssl_socket;
// TODO MOVE THIS INTO network_test AND MODIFY ITS FIXTURE
class ChatSessionIntegration : public testing::Test {
 protected:
  ChatSessionIntegration()
      : server_(server_io_context_),
        client_(client_io_context_),
        server_msg_("Sent by server") {
    server_thread_ = std::thread([this] {
      server_.await_connection([this](ssl_socket socket) {
        server_session_ = std::make_unique<chat_lib::session::chat_session>(
            server_io_context_, std::move(socket));
        server_session_->listen_msg([this](std::string,
                                           const chat_lib::util::ChatError,
                                           messages::ChatMessage msg) {
          auto msg_content = msg.msg_contents();
          server_received_msg_.set_value(msg_content);
          server_session_->send_msg(server_msg_);
        });
      });
      server_io_context_.run();
    });
  }

  ~ChatSessionIntegration() override {
    server_io_context_.stop();
    server_thread_.join();
    client_io_context_.stop();
    client_thread_.join();
  }

  std::promise<std::string> server_received_msg_;
  std::string server_msg_;
  boost::asio::io_context server_io_context_;
  boost::asio::io_context client_io_context_;
  chat_lib::networking::Server server_;
  std::unique_ptr<chat_lib::session::chat_session> server_session_;
  std::unique_ptr<chat_lib::session::chat_session> client_session_;
  chat_lib::networking::Client client_;
  std::thread server_thread_;
  std::thread client_thread_;
};

TEST_F(ChatSessionIntegration, MessageSendReceive) {
  std::promise<std::string> client_received_msg;

  std::future<std::string> client_f = client_received_msg.get_future();
  std::future<std::string> server_f = server_received_msg_.get_future();

  std::string local_ip = "localhost";

  auto client_socket = client_.try_connect(local_ip);
  client_session_ = std::make_unique<chat_lib::session::chat_session>(
      client_io_context_, std::move(client_socket));
  client_session_->listen_msg(
      [&client_received_msg](std::string, const chat_lib::util::ChatError,
                             messages::ChatMessage msg) {
        auto msg_content = msg.msg_contents();
        client_received_msg.set_value(msg_content);
      });

  client_thread_ = std::thread([this] { client_io_context_.run(); });

  std::string client_msg_ = "Sent by client";
  client_session_->send_msg(client_msg_);

  ASSERT_NE(client_f.wait_for(std::chrono::seconds(2)),
            std::future_status::timeout);
  ASSERT_NE(server_f.wait_for(std::chrono::seconds(2)),
            std::future_status::timeout);

  EXPECT_EQ(server_f.get(), client_msg_);
  EXPECT_EQ(client_f.get(), server_msg_);
}