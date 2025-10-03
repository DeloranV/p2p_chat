//
// Created by rolandpwrrt on 7.10.2025.
//

#include "../../include/core/session.h"
#include "cli/cli_management.h"
#include <boost/date_time.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <array>
#include <string>
#include "util/util.h"

namespace session {
  chat_session::chat_session(boost::asio::io_context& io_context, tcp::socket& socket)
      : socket_(socket), io_context_(io_context)
    {
      CLI::display_conn_accepted(socket_.remote_endpoint().address().to_string());
    }

    // CALLBACK FOR CLI_MANAGER - CONSOLE THREAD FROM CLI_manager::await_input CANNOT DIRECTLY CALL socket_.write_some()
    // WE NEED TO POST THE CALLBACK TO io_context EVENT LOOP
     void chat_session::send_msg(std::string msg) {
      io_context_.post(boost::bind(&chat_session::do_send_msg, this, msg));
    }

    void chat_session::do_send_msg(std::string msg) {
      boost::system::error_code error;
      std::string payload =
        utilities::serialize_message(socket_.remote_endpoint().address().to_string(), msg);

      socket_.write_some(boost::asio::buffer(payload), error);
      CLI::display_sent_msg(socket_.local_endpoint().address().to_string(), msg);
    }
    void chat_session::listen_msg() {
      socket_.async_read_some(boost::asio::buffer(rx_buf_), boost::bind(&chat_session::display_received,
        this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }


     void chat_session::display_received(const boost::system::error_code& error,
      std::size_t bytes_transferred) {
      if (!error) {
        std::string buffer_data = rx_buf_.data();
        // WHEN MESSAGE IS READ FROM A SOCKET IT FILLS THE BUFFER FROM THE BEGINNING UP TO THE LENGTH OF THE MSG ...
        // ...OVERWRITING THE PREVIOUS CHARACTERS - IF CURRENT MESSAGE IS SHORTER THAN PREVIOUS THEN THERE WILL BE ...
        // ...A PART OF THE OLDER MESSAGE STILL IN THE BUFFER
        std::string received_msg = buffer_data.substr(0, bytes_transferred);  // THEREFORE WE NEED TO READ ONLY AS MUCH AS WE GOT
        std::string deserialized = utilities::deserialize_message(received_msg);
        CLI::display_received_msg(deserialized);
        listen_msg();
      }
    }
  }
