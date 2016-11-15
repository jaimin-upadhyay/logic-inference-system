//
// Created by Jaimin Upadhyay on 11/15/2016.
//

#include <iostream>

#include "term.h"
#include "gtest/gtest.h"

TEST(TermTest, DefineValid) {
  std::string test_term_names[] = {"x", "Xyz"};
  for (std::string test_literal_name:test_term_names) {
    ASSERT_NO_THROW(Term test_literal(test_literal_name));
    Term test_literal(test_literal_name);
    EXPECT_EQ(test_literal_name, test_literal.get_name());
  }
}

TEST(ConstantTest, DefineValid) {
  std::string test_constant_names[] = {"Xyz", "James", "HarryPotter"};

  for (std::string test_constant_name:test_constant_names) {
    ASSERT_NO_THROW(Constant test_constant(test_constant_name));
    Constant test_constant(test_constant_name);
    EXPECT_EQ(test_constant_name, test_constant.get_name());
  }
}

TEST(ConstantTest, DefineInvalid) {
  std::string test_constant_names[] = {"x", "xyz", "li11y", "#@rryPotter"};

  for (std::string test_constant_name:test_constant_names) {
    EXPECT_THROW(Constant test_constant(test_constant_name),
                 std::invalid_argument);
  }
}

TEST(VariableTest, DefineValidUnassigned) {
  for (char ch = 'a'; ch <= 'z'; ch++) {
    std::string test_variable_name;
    test_variable_name.push_back(ch);
    ASSERT_NO_THROW(Variable test_variable(test_variable_name));
    Variable test_variable(test_variable_name);
    EXPECT_EQ(test_variable_name, test_variable.get_name());
    EXPECT_EQ(false, test_variable.is_assigned());
  }
}

TEST(VariableTest, DefineValidAssigned) {
  Constant test_value("TestConstant");
  for (char ch = 'a'; ch <= 'z'; ch++) {
    std::string test_variable_name;
    test_variable_name.push_back(ch);
    ASSERT_NO_THROW(Variable test_variable(test_variable_name, &test_value));
    Variable test_variable(test_variable_name, &test_value);
    EXPECT_EQ(test_variable_name, test_variable.get_name());
    ASSERT_EQ(true, test_variable.is_assigned());
    EXPECT_EQ(&test_value, test_variable.get_value());
    EXPECT_EQ(test_value.get_name(), test_variable.get_value()->get_name());
  }
}

TEST(VariableTest, DefineInvalid) {
  std::string test_variable_names[] = {"A", "Z", "xyz", "li11y", "#@rryPotter"};
  for (std::string test_variable_name:test_variable_names) {
    EXPECT_THROW(Variable test_variable(test_variable_name),
                 std::invalid_argument);
  }
}

