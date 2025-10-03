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
      while (true) {
        std::string input;
        CLI::get_user_input(input);
        callback(input);
      }
    });
  }
}