#include <gtest/gtest.h>
#include "util/util.h"
#include <iostream>

class MsgSerializationTest : public testing::Test {
protected:
  MsgSerializationTest()
    : msg_ip("127.0.0.1"),
      msg_contents("This is a test message")
  {}

  std::string msg_ip;
  std::string msg_contents;
};

TEST_F(MsgSerializationTest, SerializedToDeserialized) {
  auto timestamp = boost::posix_time::to_simple_string(
    boost::posix_time::second_clock::local_time().time_of_day());
  auto serialized = util::serialize_message(msg_ip, msg_contents);
  auto deserialized = util::deserialize_message(serialized);

  auto deserialized_str = util::msg_as_string(deserialized);
  auto expected = timestamp + " " + msg_ip + ": " + msg_contents;

  EXPECT_EQ(deserialized_str, expected);
}