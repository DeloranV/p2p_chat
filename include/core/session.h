//
// Created by rolandpwrrt on 7.10.2025.
//

#ifndef CHAT_APP_SESSION_H
#define CHAT_APP_SESSION_H

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace session {
  class chat_session {
  public:
    explicit chat_session(boost::asio::io_context& io_context, tcp::socket& socket);
    void send_msg(std::string msg);
    void do_send_msg(std::string msg);
    void listen_msg();

  private:
    void display_received(const boost::system::error_code& error, std::size_t bytes_transferred);

    std::array<char, 128> rx_buf_;
    tcp::socket& socket_;
    boost::asio::io_context& io_context_;
  };
}

#endif //CHAT_APP_SESSION_H