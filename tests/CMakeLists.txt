find_package(GTest REQUIRED)

include(GoogleTest)

add_executable(run_tests
        src/util_test.cc
        src/network_test.cc
)

enable_testing()

target_link_libraries(run_tests PRIVATE core_lib GTest::gtest_main)

gtest_discover_tests(run_tests)