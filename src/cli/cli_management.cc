//
// Created by rolandpwrrt on 7.10.2025.
//

#include <cli/cli_management.h>

namespace CLI {
   void CLI_Manager::await_input(std::function<void(std::string)> callback) {
     // callback CANNOT BE CAPTURED BY REFERENCE SINCE std:bind() USED WHEN PASSING IT HERE CREATES A TEMPORARY
     // OBJECT - AFTER THE THREAD GETS CREATED AND THIS RETURNS THE TEMPORARY FUNCTOR GETS DESTROYED AND REFERENCE
     // IS DANGLING.
     // IF WE TRIED TO PUT '&' IN THE SIGNATURE TO PASS BY REFERENCE IT WILL SHOW AN ERROR IN PLACE OF
     // std::bind() SINCE WE WILL TRY TO PASS A TEMPORARY OBJECT (RVALUE) INTO AN LVALUE REFERENCE BUT LAMBDA CAPTURES
     // DON'T EMIT THESE ERRORS.
    input_thread_ = boost::thread([callback] {
      try {
        while (true) {
          boost::this_thread::interruption_point();

          std::string input;
          CLI::get_user_input(input);

          boost::this_thread::interruption_point();

          callback(input);
        }
      } catch (const boost::thread_interrupted& e) {}
    });
  }
  CLI_Manager::~CLI_Manager() {
     std::cout << "Press ENTER to continue..." << std::endl;
     if (input_thread_.joinable()) {
       input_thread_.interrupt();
       input_thread_.join();
     }
  }
}
