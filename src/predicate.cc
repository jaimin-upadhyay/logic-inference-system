//
// Created by Jaimin Upadhyay on 11/14/2016.
//
#include <regex>
#include "predicate.h"

// Regex used to validate the predicate structure
const char Predicate::kRegex[] = "\\s*([A-Z][a-zA-Z]*)\\(([a-zA-Z,\\s]+)\\)\\s*";

// Initializes a predicate from an input string of the form:
//  Predicate(<arg 1>[, <arg 2>, <arg 3> ... <arg n>)
// Throws an invalid_argument exception if the predicate is not a case-sensitive alphabetical string that begins with an uppercase letter
Predicate::Predicate(const std::string &input_string) {
  std::invalid_argument invalid_input_string_exception(
      "Predicate should be a case-sensitive alphabetical string that begins with an uppercase letter, not like " +
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
                                       position_of_comma -
                                       position_after_last_comma);
      push_back(Term(temp_argument));
      position_after_last_comma = position_of_comma + 1;
    } while (position_of_comma != std::string::npos);
    if (size() < 1) {
      throw invalid_input_string_exception;
    }
  } else {
    throw invalid_input_string_exception;
  }
}