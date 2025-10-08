//
// Created by rolandpwrrt on 7.10.2025.
//
#include "network/client.h"
#include <boost/asio.hpp>
#include <iostream>
#include <cli/cli_management.h>

namespace networking {
  Client::Client(boost::asio::io_context &io_context)
    : io_context_(io_context),
      ctx_(ssl::context::sslv23),
      socket_(tcp::socket(io_context), ctx_),
      resolver_(io_context) {
    //ctx.set_default_verify_paths(); TODO LATER THIS ON SERVER ?
    ctx_.load_verify_file("../ssl_test_keys/server.crt");
    socket_.set_verify_mode(ssl::verify_peer);
    // socket_.set_verify_callback(
    //   std::bind(&p2p_client::verify_certificate, this, std::placeholders::_1, std::placeholders::_2));
  }

  std::shared_ptr<session::chat_session> Client::create_session(std::string &target_ip) {
    auto endpoints = resolver_.resolve(target_ip, CLI::obtain_port());
    boost::asio::connect(socket_.lowest_layer(), endpoints);
    //socket_.set_verify_callback(ssl::host_name_verification("host.name"));  TODO ?
    socket_.handshake(ssl::stream_base::client);
    // std::move SINCE WE NEED TO TRANSFER OWNERSHIP OF THE SOCKET TO THE SESSION OBJECT
    return std::make_shared<session::chat_session>(io_context_, std::move(socket_));
  }

  // TODO LEGITIMATE CERT VERIFICATION
  // bool p2p_client::verify_certificate(bool preverified, ssl::verify_context &ctx) {
  //   // The verify callback can be used to check whether the certificate that is
  //   // being presented is valid for the peer. For example, RFC 2818 describes
  //   // the steps involved in doing this for HTTPS. Consult the OpenSSL
  //   // documentation for more details. Note that the callback is called once
  //   // for each certificate in the certificate chain, starting from the root
  //   // certificate authority.
  //
  //   // In this example we will simply print the certificate's subject name.
  //   char subject_name[256];
  //   X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
  //   X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
  //   std::cout << "Verifying " << subject_name << "\n";
  //
  //   return preverified;
  // }

};