//
// Created by rolandpwrrt on 7.10.2025.
//

#ifndef CHAT_APP_SESSION_H
#define CHAT_APP_SESSION_H

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "util/message.pb.h"

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> ssl_socket;

namespace session {
  class chat_session {
  public:
    chat_session(boost::asio::io_context& io_context, ssl_socket socket);
    ~chat_session();
    // NEED TO DELETE COPY CONSTRUCTOR AND MAKE A MOVE CONSTRUCTOR, OTHERWISE WE WOULD NOT BE ABLE TO PUSH BACK INTO
    // THE session_manager VECTOR OF SESSIONS
    chat_session(chat_session&) = delete;
    chat_session(chat_session&&) noexcept;

    void end_session();
    void send_msg(std::string msg);
    void do_send_msg(std::string msg);
    void listen_msg(std::function<void(std::string)> handler);
    void display_sent(std::string msg);
    std::string get_local_address();
    std::string get_remote_address();

  private:
    void display_received();
    void save_received(const boost::system::error_code& error, std::size_t bytes_transferred, std::function<void(std::string)> handler);

    std::array<char, 128> rx_buf_;
    ssl_socket socket_;
    std::string last_received_msg;
    boost::asio::io_context& io_context_;
  };
}

#endif //CHAT_APP_SESSION_H