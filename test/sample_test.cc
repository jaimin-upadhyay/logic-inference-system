//
// Created by Jaimin Upadhyay on 11/12/2016.
//
#include "knowledge_base.h"
#include "gtest/gtest.h"

TEST(SampleTest, AskTest) {
  const int kNoOfSamples = 49;
  ASSERT_THROW(KnowledgeBase::Query("in", "out"), std::invalid_argument);
  for (int i = 0; i <= kNoOfSamples; i++) {
    std::cout << "Sample " << i << ": " << std::endl;
    std::ostringstream input_file_name_stream, output_file_name_stream;
    input_file_name_stream << "input_" << i << ".txt";
    output_file_name_stream << "output_" << i << ".txt";
    ASSERT_NO_THROW(KnowledgeBase::Query(input_file_name_stream.str(),
                                         output_file_name_stream.str()));
    KnowledgeBase::Query(input_file_name_stream.str(),
                         output_file_name_stream.str());
    std::ostringstream expected_output_file_name_stream;
    expected_output_file_name_stream << "expected_output_" << i << ".txt";
    std::ifstream expected_output_stream(
        expected_output_file_name_stream.str());
    std::ifstream output_stream(output_file_name_stream.str());
    std::string output_line, expected_output_line;
    int query_number = 1;
    while (std::getline(output_stream, output_line) &&
           std::getline(expected_output_stream, expected_output_line)) {
      EXPECT_EQ(expected_output_line, output_line)
                << "Query " << query_number;
      query_number++;
    }
    ASSERT_FALSE(std::getline(output_stream, output_line));
    ASSERT_FALSE(std::getline(expected_output_stream, expected_output_line));
    expected_output_stream.close();
    output_stream.close();
  }
}
