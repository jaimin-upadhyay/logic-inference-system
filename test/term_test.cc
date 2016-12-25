//
// Created by Jaimin Upadhyay on 11/15/2016.
//

#include <iostream>

#include "term.h"
#include "gtest/gtest.h"

TEST(TermTest, DefineInvalid) {
  std::string test_constant_names[] = {"xyz", "li11y", "#@rryPotter"};

  for (std::string test_constant_name:test_constant_names) {
    EXPECT_THROW(Term test_constant(test_constant_name),
                 std::invalid_argument);
  }
}

TEST(TermTest, DefineValidConstant) {
  std::string test_constant_names[] = {"Xyz", "James", "HarryPotter"};

  for (std::string test_constant_name:test_constant_names) {
    ASSERT_NO_THROW(Term test_constant(test_constant_name));
    Term test_constant(test_constant_name);
    EXPECT_EQ(true, test_constant.is_constant());
    EXPECT_EQ(test_constant_name, test_constant.get_name());
    EXPECT_EQ(test_constant_name, test_constant.to_string());
  }
}

TEST(TermTest, DefineValidVariable) {
  for (char ch = 'a'; ch <= 'z'; ch++) {
    std::string test_variable_name;
    test_variable_name.push_back(ch);
    ASSERT_NO_THROW(Term test_variable(test_variable_name));
    Term test_variable(test_variable_name);
    EXPECT_EQ(false, test_variable.is_constant());
    EXPECT_EQ(test_variable_name, test_variable.get_name());
    EXPECT_EQ(test_variable_name, test_variable.to_string());
  }
}

TEST(TermTest, ConstantsComparision) {
  Term test_constant_one("Harry"), test_constant_two("Hermione");
  EXPECT_EQ(false, test_constant_one == test_constant_two);
  EXPECT_EQ(true, test_constant_one != test_constant_two);
  EXPECT_EQ(true, test_constant_one < test_constant_two);
  EXPECT_EQ(false, test_constant_one > test_constant_two);
  EXPECT_EQ(true, test_constant_one <= test_constant_two);
  EXPECT_EQ(false, test_constant_one >= test_constant_two);
  EXPECT_EQ(true, test_constant_one == test_constant_one);
  EXPECT_EQ(false, test_constant_one != test_constant_one);
  EXPECT_EQ(false, test_constant_one < test_constant_one);
  EXPECT_EQ(false, test_constant_one > test_constant_one);
  EXPECT_EQ(true, test_constant_one <= test_constant_one);
  EXPECT_EQ(true, test_constant_one >= test_constant_one);
}

TEST(TermTest, VariablesComparision) {
  Term test_variable_one("j"), test_variable_two("z");
  EXPECT_EQ(false, test_variable_one == test_variable_two);
  EXPECT_EQ(true, test_variable_one != test_variable_two);
  EXPECT_EQ(true, test_variable_one < test_variable_two);
  EXPECT_EQ(false, test_variable_one > test_variable_two);
  EXPECT_EQ(true, test_variable_one <= test_variable_two);
  EXPECT_EQ(false, test_variable_one >= test_variable_two);
  EXPECT_EQ(true, test_variable_one == test_variable_one);
  EXPECT_EQ(false, test_variable_one != test_variable_one);
  EXPECT_EQ(false, test_variable_one < test_variable_one);
  EXPECT_EQ(false, test_variable_one > test_variable_one);
  EXPECT_EQ(true, test_variable_one <= test_variable_one);
  EXPECT_EQ(true, test_variable_one >= test_variable_one);
}

TEST(TermTest, ConstantToVariableComparision) {
  Term test_term_one("Hermoine"), test_term_two("j");
  EXPECT_EQ(false, test_term_one == test_term_two);
  EXPECT_EQ(true, test_term_one != test_term_two);
  EXPECT_EQ(true, test_term_one < test_term_two);
  EXPECT_EQ(false, test_term_one > test_term_two);
  EXPECT_EQ(true, test_term_one <= test_term_two);
  EXPECT_EQ(false, test_term_one >= test_term_two);
}