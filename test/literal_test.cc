//
// Created by Jaimin on 12/18/2016.
//
#include "literal.h"
#include "gtest/gtest.h"

TEST(LiteralTest, Comparison) {
  Literal test_literal_one("Student(Hogwarts,HarryPotter)"), test_literal_two(
      "Student(Hogwarts,HermioneGranger)"), test_literal_three(
      "~Student(Hogwarts,HermioneGranger)");
  EXPECT_EQ(false, test_literal_one == test_literal_two);
  EXPECT_EQ(true, test_literal_one != test_literal_two);
  EXPECT_EQ(true, test_literal_one < test_literal_two);
  EXPECT_EQ(false, test_literal_one > test_literal_two);
  EXPECT_EQ(true, test_literal_one <= test_literal_two);
  EXPECT_EQ(false, test_literal_one >= test_literal_two);

  EXPECT_EQ(true, test_literal_one == test_literal_one);
  EXPECT_EQ(false, test_literal_one != test_literal_one);
  EXPECT_EQ(false, test_literal_one < test_literal_one);
  EXPECT_EQ(false, test_literal_one > test_literal_one);
  EXPECT_EQ(true, test_literal_one <= test_literal_one);
  EXPECT_EQ(true, test_literal_one >= test_literal_one);

  EXPECT_EQ(false, test_literal_two == test_literal_three);
  EXPECT_EQ(true, test_literal_two != test_literal_three);
  EXPECT_EQ(true, test_literal_two < test_literal_three);
  EXPECT_EQ(false, test_literal_two > test_literal_three);
  EXPECT_EQ(true, test_literal_two <= test_literal_three);
  EXPECT_EQ(false, test_literal_two >= test_literal_three);
}


