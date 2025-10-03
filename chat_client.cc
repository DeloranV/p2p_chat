#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: chat_client <server_ip>" << '\n';
    return 1;
  }
  boost::asio::io_context io_context;
  tcp::resolver resolver(io_context);
  tcp::resolver::results_type endpoints =
    resolver.resolve(argv[1], "34567");
  tcp::socket socket(io_context);
  boost::asio::connect(socket, endpoints);

  for (;;) {
    std::cout << "Type message and press enter: ";
    std::string msg;
    std::getline(std::cin, msg);

    boost::system::error_code ignored_error;
    boost::asio::write(socket, boost::asio::buffer(msg), ignored_error);
  }

  return 0;
}