#include <gtest/gtest.h>
#include "channel.h"
#include <variant>
#include <thread>
#include <string>

void read_channel(channel::channel<std::string>& pipe, std::vector<std::string>& result) {
  while (true) {
    auto elem = pipe.receive();
    if (!elem) {
      return;  // pipe is closed
    }
    result.push_back(std::move(elem.value()));
  }
}

void read_channel(channel::multi_types_channel<int, std::string>& pipe, std::vector<std::string>& result) {
  while (true) {
    auto elem = pipe.receive();
    if (!elem) {
      return;  // pipe is closed
    }
    if (std::holds_alternative<std::string>(elem.value())) {
      result.push_back(std::get<std::string>(elem.value()));
    }
    else if (std::holds_alternative<int>(elem.value())) {
      result.push_back(std::to_string(std::get<int>(elem.value())));
    }
  }
}

TEST(channel_test, one_type) {
  channel::channel<std::string> pipe;
  pipe.send("titi");
  pipe.send("tata");
  pipe.send("tutu");

  std::vector<std::string> result;
  pipe.close();
  read_channel(pipe, result);

  EXPECT_EQ(result.size(), 3);
  EXPECT_EQ(result[0], "titi");
  EXPECT_EQ(result[1], "tata");
  EXPECT_EQ(result[2], "tutu");
}

TEST(channel_test, one_type_read_in_second_thread) {

  channel::channel<std::string> pipe;
  std::vector<std::string> result;

  std::thread read_pipe_thread([&]() { read_channel(pipe, result); });

  pipe.send("titi");
  pipe.send("tata");
  pipe.send("tutu");
  pipe.close();
  read_pipe_thread.join();

  EXPECT_EQ(result.size(), 3);
  EXPECT_EQ(result[0], "titi");
  EXPECT_EQ(result[1], "tata");
  EXPECT_EQ(result[2], "tutu");
}

TEST(channel_test, multi_type) {
  channel::multi_types_channel<int, std::string> pipe;
  pipe.send("titi");
  pipe.send(4);
  pipe.send("tutu");
  pipe.send(12);

  std::vector<std::string> result;
  pipe.close();
  read_channel(pipe, result);

  EXPECT_EQ(result.size(), 4);
  EXPECT_EQ(result[0], "titi");
  EXPECT_EQ(result[1], "4");
  EXPECT_EQ(result[2], "tutu");
  EXPECT_EQ(result[3], "12");
}

TEST(channel_test, multi_type_read_in_second_thread) {
  channel::multi_types_channel<int, std::string> pipe;
  std::vector<std::string> result;

  std::thread read_pipe_thread([&]() { read_channel(pipe, result); });

  pipe.send("titi");
  pipe.send(4);
  pipe.send("tutu");
  pipe.send(12);

  pipe.close();
  read_pipe_thread.join();

  EXPECT_EQ(result.size(), 4);
  EXPECT_EQ(result[0], "titi");
  EXPECT_EQ(result[1], "4");
  EXPECT_EQ(result[2], "tutu");
  EXPECT_EQ(result[3], "12");
}
