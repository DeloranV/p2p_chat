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
    // SOCKET TAKEN BY RVALUE SINCE SESSION WILL BE THE OWNER
    // OWNERSHIP OF SOCKET PASSED BY VALUE FOR VERSATILE API - WILL ACCEPT BOTH LVALUE AND RVALUE INSTEAD OF JUST RVAL
    chat_session::chat_session(boost::asio::io_context &io_context, ssl_socket socket)
        : socket_(std::move(socket)), io_context_(io_context) {
        CLI::display_conn_accepted(socket_.lowest_layer().remote_endpoint().address().to_string());
    }

    chat_session::~chat_session() {
        std::cout << "session destructor" << std::endl;
        socket_.lowest_layer().shutdown(tcp::socket::shutdown_both);
        socket_.lowest_layer().close();
    }

    void chat_session::end_session() {
        io_context_.stop();
    }

    // CALLBACK FOR CLI_MANAGER - CONSOLE THREAD FROM CLI_manager::await_input CANNOT DIRECTLY CALL socket_.write_some()
    // WE NEED TO POST THE CALLBACK TO io_context EVENT LOOP
    void chat_session::send_msg(std::string msg) {
        if (msg == ":!q") {
            end_session();
            return;
        }
        io_context_.post(boost::bind(&chat_session::do_send_msg, this, msg));
    }

    void chat_session::do_send_msg(std::string msg) {
        boost::system::error_code error;
        std::string payload =
                util::serialize_message(socket_.lowest_layer().remote_endpoint().address().to_string(), msg);

        socket_.write_some(boost::asio::buffer(payload), error);
        CLI::display_sent_msg(socket_.lowest_layer().local_endpoint().address().to_string(), msg);
    }

    void chat_session::listen_msg() {
        socket_.async_read_some(boost::asio::buffer(rx_buf_), boost::bind(&chat_session::display_received,
                                                                          this, boost::asio::placeholders::error,
                                                                          boost::asio::placeholders::bytes_transferred));
    }

    void chat_session::display_received(const boost::system::error_code &error,
                                        std::size_t bytes_transferred) {
        if (error == ssl::error::stream_truncated) {
            CLI::overwrite_prompt_character();
            std::cout << "Remote host has disconnected\n" << std::endl;
            end_session();
        }
        if (!error) {
            std::string buffer_data = rx_buf_.data();
            // WHEN MESSAGE IS READ FROM A SOCKET IT FILLS THE BUFFER FROM THE BEGINNING UP TO THE LENGTH OF THE MSG ...
            // ...OVERWRITING THE PREVIOUS CHARACTERS - IF CURRENT MESSAGE IS SHORTER THAN PREVIOUS THEN THERE WILL BE ...
            // ...A PART OF THE OLDER MESSAGE STILL IN THE BUFFER
            std::string received_msg = buffer_data.substr(0, bytes_transferred);
            // THEREFORE WE NEED TO READ ONLY AS MUCH AS WE GOT
            std::string deserialized = util::deserialize_message(received_msg);
            CLI::display_received_msg(deserialized);
            listen_msg();
        }
    }
}
