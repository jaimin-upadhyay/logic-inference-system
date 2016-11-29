project(homework3_tests)

add_subdirectory(lib/gtest-1.7.0)

add_executable(homework3-test input_test.cc term_test.cc predicate_test.cc sentence_test.cc knowledge_base_test.cc)
target_link_libraries(homework3-test gtest gtest_main)
target_link_libraries(homework3-test homework3)