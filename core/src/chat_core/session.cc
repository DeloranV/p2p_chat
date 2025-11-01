//
// Created by rolandpwrrt on 7.10.2025.
//

#include "chat_core/session.h"
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
        : socket_(std::move(socket)),
          io_context_(io_context)
    {}

    chat_session::~chat_session() {
        socket_.lowest_layer().shutdown(tcp::socket::shutdown_both);
        socket_.lowest_layer().close();
    }

    chat_session::chat_session(chat_session&& session) noexcept
        : socket_(std::move(session.socket_)),
          io_context_(io_context_)
    {}

    std::string chat_session::get_local_address() {
        return socket_.lowest_layer().local_endpoint().address().to_string();
    }

    std::string chat_session::get_remote_address() {
        return socket_.lowest_layer().remote_endpoint().address().to_string();
    }

    // CALLBACK FOR CLI_MANAGER - CONSOLE THREAD FROM CLI_manager::await_input CANNOT DIRECTLY CALL socket_.write_some()
    // WE NEED TO POST THE CALLBACK TO io_context EVENT LOOP
    void chat_session::send_msg(std::string msg) {
        io_context_.post(boost::bind(&chat_session::do_send_msg, this, msg));
    }

    void chat_session::do_send_msg(std::string msg) {
        boost::system::error_code error;
        std::string payload =
                util::serialize_message(socket_.lowest_layer().local_endpoint().address().to_string(), msg);

        socket_.write_some(boost::asio::buffer(payload), error);
    }

    // TODO NOW THIS SHOULD BE HANDLED BY THE listen_msg HANDLER BY THE LIB USER
    // void chat_session::display_sent(std::string msg) {
    //     std::string payload =
    //             util::sent_message(socket_.lowest_layer().local_endpoint().address().to_string(), msg);
    //     emit session_adapter_.message_received(QString(payload.c_str()));
    // }

    void chat_session::listen_msg(std::function<void(std::string)> handler) {
        socket_.async_read_some(boost::asio::buffer(rx_buf_), boost::bind(&chat_session::save_received,
                                                                          this, boost::asio::placeholders::error,
                                                                          boost::asio::placeholders::bytes_transferred, handler));
    }

    void chat_session::save_received(const boost::system::error_code &error,
        std::size_t bytes_transferred, std::function<void(std::string)> handler) {
        if (!error) {
            std::string buffer_data = rx_buf_.data();
            // WHEN MESSAGE IS READ FROM A SOCKET IT FILLS THE BUFFER FROM THE BEGINNING UP TO THE LENGTH OF THE MSG ...
            // ...OVERWRITING THE PREVIOUS CHARACTERS - IF CURRENT MESSAGE IS SHORTER THAN PREVIOUS THEN THERE WILL BE ...
            // ...A PART OF THE OLDER MESSAGE STILL IN THE BUFFER
            std::string serialized = buffer_data.substr(0, bytes_transferred);
            auto deserialized = util::deserialize_message(serialized);
            last_received_msg = util::msg_as_string(deserialized);
            handler(last_received_msg);
            //display_received();
        }
        listen_msg(handler);
    }

    // TODO NOW THIS SHOULD BE HANDLED BY THE listen_msg HANDLER BY THE LIB USER
    // void chat_session::display_received() {
    //     // if (error == ssl::error::stream_truncated) {
    //     //     CLI::overwrite_prompt_character();
    //     //     std::cout << "Remote host has disconnected\n" << std::endl;
    //     //     end_session();
    //     // }
    //     // if (!error) {
    //         // WHEN MESSAGE IS READ FROM A SOCKET IT FILLS THE BUFFER FROM THE BEGINNING UP TO THE LENGTH OF THE MSG ...
    //         // ...OVERWRITING THE PREVIOUS CHARACTERS - IF CURRENT MESSAGE IS SHORTER THAN PREVIOUS THEN THERE WILL BE ...
    //         // ...A PART OF THE OLDER MESSAGE STILL IN THE BUFFER
    //         emit session_adapter_.message_received(QString(last_received_msg.c_str()));
    //     // }
    // }
}
