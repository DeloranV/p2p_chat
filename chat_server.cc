#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main() {
  try {
    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 34567));
    tcp::socket socket(io_context);
    acceptor.accept(socket);

    for (;;) {
      std::array<char, 128> buf;
      boost::system::error_code error;

      size_t len = socket.read_some(boost::asio::buffer(buf), error);
      if (error) throw boost::system::system_error(error);

      std::cout.write(buf.data(), len) << '\n';
    }
  }
  catch (std::exception& e) {
    std::cerr << e.what() << '\n';
  }
  return 0;
}
