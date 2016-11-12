project(homework3_tests)

add_subdirectory(lib/gtest-1.7.0)

add_executable(homework3-test input_test.cpp)
target_link_libraries(homework3-test gtest gtest_main)
target_link_libraries(homework3-test homework3)