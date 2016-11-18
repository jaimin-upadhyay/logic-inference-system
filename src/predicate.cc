//
// Created by Jaimin Upadhyay on 11/14/2016.
//
#include <regex>
#include "predicate.h"

// Regex used to validate the predicate structure
const char Predicate::kRegex[] = "([A-Z][a-zA-Z]*)\\((.+)*\\)";

// Initializes a predicate from an input string of the form:
// Predicate(<arg 1>[, <arg 2>, <arg 3> ... <arg n>)
// Throws an invalid_argument exception if the predicate is not a case-sensitive alphabetical string that begins with an uppercase letter
Predicate::Predicate(const std::string &input_string) {
  std::invalid_argument invalid_input_string_exception(
      "Predicate should be a case-sensitive alphabetical string that begins with an uppercase letter, not like" +
      input_string);
  std::regex predicate_regex(kRegex);
  std::smatch predicate_match_result;
  if (std::regex_match(input_string, predicate_match_result, predicate_regex)) {
    Predicate::name_ = predicate_match_result[1].str();
    std::string arguments = predicate_match_result[2].str(), temp_argument;
    size_t position_of_comma;
    size_t position_after_last_comma = 0;
    do {
      position_of_comma = arguments.find(',',
                                         position_after_last_comma);
      temp_argument = arguments.substr(position_after_last_comma,
                                       position_of_comma - position_after_last_comma);
      Predicate::AddArgument(temp_argument);
      position_after_last_comma = position_of_comma + 1;
    } while (position_of_comma != std::string::npos);
    if (Predicate::arguments_.size() < 1) {
      throw invalid_input_string_exception;
    }
  } else {
    throw invalid_input_string_exception;
  }
}

// Validates the name of the predicate to be a case-sensitive alphabetical string that begins with an uppercase letter
void Predicate::set_name(const std::string &name) {
  if (std::regex_match(name, std::regex("[A-Z][a-zA-Z]*"))) {
    Predicate::name_ = name;
  } else {
    throw std::invalid_argument(
        "Predicate should be a case-sensitive alphabetical string");
  }
}

// Validates the number of arguments to the predicate to be at least one
void Predicate::set_arguments(const std::vector<Term> &arguments) {
  if (!arguments.empty()) {
    Predicate::arguments_ = arguments;
  } else {
    throw std::invalid_argument("Predicate should have at least one argument");
  }
}

// Adds a input string to the arguments if it is a valid term i.e. a variable or a constant
void Predicate::AddArgument(std::string input_string) {
  Term *new_argument = nullptr;
  try {
    new_argument = new Variable(input_string);
  } catch (std::invalid_argument) {
    new_argument = new Constant(input_string);
  }
  arguments_.push_back(*new_argument);
  delete new_argument;
}
