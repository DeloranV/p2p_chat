//
// Created by rolandpwrrt on 7.10.2025.
//

#ifndef CHAT_APP_SESSION_H
#define CHAT_APP_SESSION_H

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "core/session_adapter.h"

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> ssl_socket;

namespace session {
  class chat_session {
  public:
    explicit chat_session(boost::asio::io_context& io_context, ssl_socket socket, SessionAdapter& adapter);
    ~chat_session();
    void end_session();
    void send_msg(std::string msg);
    void do_send_msg(std::string msg);
    void listen_msg();
    void display_sent(std::string msg);

  private:
    void display_received(const boost::system::error_code& error, std::size_t bytes_transferred);

    std::array<char, 128> rx_buf_;
    ssl_socket socket_;
    boost::asio::io_context& io_context_;
    SessionAdapter& session_adapter_;
  };
}

#endif //CHAT_APP_SESSION_H