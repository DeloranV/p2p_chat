//
// Created by rolandpwrrt on 28.10.2025.
//

#ifndef CHAT_APP_SESSION_MANAGR_H
#define CHAT_APP_SESSION_MANAGR_H

#include "chat_core/session.h"
#include "session_adapter.h"
// TEST FOR A SINGLE SESSION
// MULTIPLE SESSIONS WILL NEED TO HAVE SOME METADATA LIKE SESSION REMOTE HOST IP SO THAT WE CAN FIND THE APPROPRIATE
typedef ssl::stream<tcp::socket> ssl_socket;
class SessionManager {
public:
  SessionManager(boost::asio::io_context& io_context, std::shared_ptr<SessionAdapter> adapter);
  void start_session(ssl_socket socket, SessionAdapter& adapter);
  void close_session(std::string remote_host_ip);
  //void get_session(/*session id*/, /*remote_host_ip*/) TODO MAYBE SOMETHING LIKE THIS FOR MULTIPLE SESSIONS?
  session::chat_session* get_session(std::string remote_host_ip); // TODO NODISCARD
  [[nodiscard]] bool is_session_active(std::string remote_host_ip);
  void temp(std::string);
  void temp_handler(std::string remote_endpoint, const util::ChatError err, messages::ChatMessage msg);
private:
  // MAYBE HOLD SESSION ADAPTER HERE INSTEAD OF SESSIONS ?
  boost::asio::io_context& io_context_;
  std::shared_ptr<SessionAdapter> adapter_;
  std::vector<std::unique_ptr<session::chat_session>> sessions_;
  // std::shared_ptr<session::chat_session> single_session_;

};

#endif //CHAT_APP_SESSION_MANAGR_H