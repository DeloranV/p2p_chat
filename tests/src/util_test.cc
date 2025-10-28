#include <gtest/gtest.h>
#include "util/util.h"

class MsgSerializationTest : public testing::Test {
protected:
  MsgSerializationTest()
    : msg_ip("127.0.0.1"),
      msg_contents("This is a test message")
  {}

  std::string msg_ip;
  std::string msg_contents;
};

TEST_F(MsgSerializationTest, CorrectSerializationFormat) {
  auto timestamp = boost::posix_time::to_simple_string(
    boost::posix_time::second_clock::local_time().time_of_day());
  auto serialized = util::serialize_message(msg_ip, msg_contents);
  auto expected = timestamp + "|" + msg_contents + "|" + msg_ip;

  ASSERT_EQ(serialized, expected);
}

TEST_F(MsgSerializationTest, CorrectDeserializationFormat) {
  auto timestamp = boost::posix_time::to_simple_string(
    boost::posix_time::second_clock::local_time().time_of_day());
  std::string serialized_msg = timestamp + "|This is a test message|127.0.0.1";
  auto deserialized_msg = util::deserialize_message(serialized_msg);

  auto expected = timestamp + " " + msg_ip + ": " + msg_contents;

  ASSERT_EQ(deserialized_msg, expected);
}

// TEST_F(MsgSerializationTest, SerializedToDeserialized) {
//   auto serialized = util::serialize_message(msg_ip, msg_contents);
//   auto deserialized = util::deserialize_message(serialized);
//
//
// }