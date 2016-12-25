//
// Created by Jaimin Upadhyay on 11/15/2016.
//

#include "predicate.h"
#include "gtest/gtest.h"

TEST(PredicateTest, DefineValid) {
  std::string test_predicate_names[] = {"Xyz", "James", "HarryPotter"};
  std::vector<Term> test_arguments;
  Term test_term("TestTerm");
  test_arguments.push_back(test_term);
  for (std::string test_predicate_name:test_predicate_names) {
    ASSERT_NO_THROW(
        Predicate test_predicate(test_predicate_name, test_arguments));
    Predicate test_predicate(test_predicate_name, test_arguments);
    EXPECT_EQ(test_predicate_name, test_predicate.get_name());
    EXPECT_EQ(test_arguments.size(), test_predicate.size());
    EXPECT_EQ(test_arguments, test_predicate);
  }
}

TEST(PredicateTest, DefineInvalidName) {
  std::string test_predicate_names[] = {"xyz", "li11y",
                                        "#@rryPotter"};
  std::vector<Term> test_arguments;
  Term test_term("TestTerm");
  test_arguments.push_back(test_term);
  for (std::string test_predicate_name:test_predicate_names) {
    EXPECT_THROW(Predicate test_predicate(test_predicate_name, test_arguments),
                 std::invalid_argument);
  }
}

TEST(PredicateTest, DefineInvalidArguments) {
  std::string test_predicate_name = "Hermoine";
  std::vector<Term> test_arguments;
  EXPECT_THROW(Predicate test_predicate(test_predicate_name, test_arguments),
               std::invalid_argument);
}

void TestPredicateString(std::string test_predicate_string, std::string test_predicate_name,
                         std::vector<Term> test_arguments) {
  ASSERT_NO_THROW(Predicate(test_predicate_name, test_arguments));
  Predicate test_predicate(test_predicate_string);
  EXPECT_EQ(test_predicate_name, test_predicate.get_name());
  ASSERT_EQ(test_arguments.size(),
            test_predicate.size());

  for (int i = 0; i < test_arguments.size(); i++) {
    EXPECT_EQ(test_arguments[i].get_name(),
              test_predicate[i].get_name());
  }
  EXPECT_EQ(test_predicate_string, test_predicate.to_string());
}

TEST(PredicateTest, DefineFromValidString) {
  std::string test_predicate_strings[] = {"Student(Hogwarts,HarryPotter)",
                                          "Joker(u)", "Student(Hogwarts,HarryPotter,Wizard)"};
  std::string test_predicate_names[] = {"Student", "Joker"};
  std::vector<Term> test_arguments[3] = {std::vector<Term>()};
  Term test_constant[3] = {Term("Hogwarts"), Term("HarryPotter"),
                           Term("Wizard")};
  test_arguments[0].push_back(test_constant[0]);
  test_arguments[0].push_back(test_constant[1]);

  TestPredicateString(test_predicate_strings[0], test_predicate_names[0], test_arguments[0]);

  Term test_variable("u");
  test_arguments[1].push_back(test_variable);

  TestPredicateString(test_predicate_strings[1], test_predicate_names[1], test_arguments[1]);

  test_arguments[2].push_back(test_constant[0]);
  test_arguments[2].push_back(test_constant[1]);
  test_arguments[2].push_back(test_constant[2]);
  TestPredicateString(test_predicate_strings[2], test_predicate_names[0], test_arguments[2]);
}

TEST(PredicateTest, DefineFromInvalidString) {
  std::string test_predicate_strings[] = {"student(xyz)", "Student()",
                                          "Student(li11y)",
                                          "Student(Hogwarts, #@rryPotter)"};
  for (std::string test_predicate_string:test_predicate_strings) {
    EXPECT_THROW(Predicate test_predicate(test_predicate_string),
                 std::invalid_argument);
  }
}

TEST(PredicateTest, Comparision) {
  Predicate test_predicate_one(
      "Student(Hogwarts,HarryPotter)"), test_predicate_two(
      "Student(Hogwarts,HermioneGranger)");
  EXPECT_EQ(false, test_predicate_one == test_predicate_two);
  EXPECT_EQ(true, test_predicate_one != test_predicate_two);
  EXPECT_EQ(true, test_predicate_one < test_predicate_two);
  EXPECT_EQ(false, test_predicate_one > test_predicate_two);
  EXPECT_EQ(true, test_predicate_one <= test_predicate_two);
  EXPECT_EQ(false, test_predicate_one >= test_predicate_two);
  EXPECT_EQ(true, test_predicate_one == test_predicate_one);
  EXPECT_EQ(false, test_predicate_one != test_predicate_one);
  EXPECT_EQ(false, test_predicate_one < test_predicate_one);
  EXPECT_EQ(false, test_predicate_one > test_predicate_one);
  EXPECT_EQ(true, test_predicate_one <= test_predicate_one);
  EXPECT_EQ(true, test_predicate_one >= test_predicate_one);
}