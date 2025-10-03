#include <iostream>
#include <boost/asio.hpp>
#include "core/app.h"

// FOR MULTIPLE CHAT SESSIONS - DO A VECTOR OF CHAT SESSIONS AND PASS OWNERSHIP OF SOCKETS TO THEM ?
// DO A SESSION MANAGER OBJECT HOLDING AND MANAGING THE SESSIONS - THEN SERVER AND CLIENT WOULD HOLD ONLY THE MANAGER
// DO A CLI MANAGER FOR CONSOLE INPUT/OUTPUT
// DO ENCRYPTION WITH BOOST

int main(int argc, char* argv[]) {
  boost::asio::io_context io_context;
  if (argc == 1) {
    CLI_application app(io_context, utilities::Mode::SERVER);
    app.run_server();
  }
  else if (argc == 2) {
    CLI_application app(io_context, utilities::Mode::CLIENT);
    std::string target_ip = argv[1];
    app.run_client(target_ip);
  }
  else {
    std::cout << "Usage: \n Server: chat_app \n Client: chat_app <target_ip> \n";
  }

  return 0;
}