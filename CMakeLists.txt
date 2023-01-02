cmake_minimum_required(VERSION 3.15)
project(channels)

find_package(GTest)

set(SOURCES src/lib/channel.h)

add_executable(channels_tests src/test/channel_test.cpp ${SOURCES})
target_compile_features(channels_tests PRIVATE cxx_std_17)
target_include_directories(channels_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/lib)

target_link_libraries(channels_tests PRIVATE GTest::gtest GTest::gtest_main)

