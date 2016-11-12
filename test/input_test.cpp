//
// Created by Jaimin Upadhyay on 11/12/2016.
//
#include "input.h"

#include "gtest/gtest.h"

TEST(InputTest, ReadInput) {
    std::vector<std::string> expectedQueries{"F(Bob)",
                                             "H(John)",
                                             "~H(Alice)",
                                             "~H(John)",
                                             "G(Bob)",
                                             "G(Tom)"};
    std::vector<std::string> expectedKB{"A(x) => H(x)",
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
    Input input;
    input.readFrom("input.txt");
    std::vector<std::string> queries = input.getQueries();
    std::vector<std::string> kb = input.getKnowledgeBase();

    ASSERT_EQ(expectedQueries.size(), queries.size());
    for (int i = 0; i < queries.size(); i++) {
        EXPECT_EQ(expectedQueries[i], queries[i]) << "\t\ti: " << i;
    }
    ASSERT_EQ(expectedKB.size(), kb.size());
    for (int i = 0; i < kb.size(); i++) {
        EXPECT_EQ(expectedKB[i], kb[i]) << "\t\ti: " << i;
    }
}
