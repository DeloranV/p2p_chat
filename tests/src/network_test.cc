#include <gtest/gtest.h>

#include <chrono>
#include <future>

#include "boost/asio.hpp"
#include "network/client.h"
#include "network/server.h"

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> ssl_socket;

class ServerClientIntegration : public testing::Test {
 protected:
  ServerClientIntegration() : server_(new chat_lib::networking::Server(io_context_)), client_(io_context_) {
    server_thread_ = std::thread([this] {
      server_->await_connection([this](ssl_socket socket) {
        server_connect_success_.set_value(socket.lowest_layer().is_open());
      });
      io_context_.run();
    });
  }

  ~ServerClientIntegration() override {
    io_context_.stop();
    server_thread_.join();
  }

  std::promise<bool> server_connect_success_;
  boost::asio::io_context io_context_;
  std::shared_ptr<chat_lib::networking::Server> server_;
  chat_lib::networking::Client client_;
  std::thread server_thread_;
};

TEST_F(ServerClientIntegration, ConnectionHandshake) {
  std::future<bool> server_f = server_connect_success_.get_future();
  std::string local_ip = "localhost";
  bool client_connect_success = false;

  auto client_socket = client_.try_connect(local_ip);
  client_connect_success = client_socket.lowest_layer().is_open();

  server_f.wait_for(std::chrono::seconds(1));

  // THIS NEEDS TO PASS OTHERWISE THE SESSION INTEGRATION TEST WILL FAIL
  ASSERT_EQ(server_f.get(), client_connect_success);
}