//
// Created by Jaimin Upadhyay on 11/12/2016.
//

#include "input.h"

#include "gtest/gtest.h"

class InputTest : public ::testing::Test {
protected:
    std::vector<std::string> expected_queries_{"F(Bob)",
                                             "H(John)",
                                             "~H(Alice)",
                                             "~H(John)",
                                             "G(Bob)",
                                             "G(Tom)"};
    std::vector<std::string> expected_knowledge_base_{"A(x) => H(x)",
                                                      "D(x,y) => ~H(y)",
                                                      "B(x,y) ^ C(x,y) => A(x)",
                                                      "B(John,Alice)",
                                                      "B(John,Bob)",
                                                      "D(x,y) ^ Q(y) => C(x,y)",
                                                      "D(John,Alice)",
                                                      "Q(Bob)",
                                                      "D(John,Bob)",
                                                      "F(x) => G(x)",
                                                      "G(x) => H(x)",
                                                      "H(x) => F(x)",
                                                      "R(x) => H(x)",
                                                      "R(Tom)"};
    std::string input_file_name_ = "input.txt";
    std::string output_file_name_ = "output.txt";
};

TEST_F(InputTest, ReadInput) {
    Input input;
    input.ReadFrom(input_file_name_);
    std::vector<std::string> queries = input.get_queries();
    std::vector<std::string> kb = input.get_knowledge_base();

    ASSERT_EQ(expected_queries_.size(), queries.size());
    for (int i = 0; i < queries.size(); i++) {
        EXPECT_EQ(expected_queries_[i], queries[i]) << "\t\ti: " << i;
    }

    ASSERT_EQ(expected_knowledge_base_.size(), kb.size());
    for (int i = 0; i < kb.size(); i++) {
        EXPECT_EQ(expected_knowledge_base_[i], kb[i]) << "\t\ti: " << i;
    }
}
