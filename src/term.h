//
// Created by Jaimin Upadhyay on 11/15/2016.
//
// Defines all the terms of the logic system

#ifndef HOMEWORK3_SRC_TERM_H
#define HOMEWORK3_SRC_TERM_H

#include <iostream>
#include <regex>

// Describes the terms of the logic sentences
class Term {
public:
  static const char kConstantRegex[];
  static const char kVariableRegex[];

  Term(const std::string &input_string) {
    try {
      constant_ = false;
      set_name(input_string, kVariableRegex, kVariableErrorMessage);
    } catch (std::invalid_argument) {
      try {
        constant_ = true;
        set_name(input_string, kConstantRegex, kConstantErrorMessage);
      } catch (std::invalid_argument) {
        throw std::invalid_argument(
            "Input string is not a variable or a constant term");
      }
    }
  }

  std::string to_string() const {
    std::ostringstream term_string_stream;
    term_string_stream << *this;
    return term_string_stream.str();
  }

  void set_name(const std::string &name) {
    if (!is_constant()) {
      set_name(name, kVariableRegex, kVariableErrorMessage);
    }
  }

  const std::string &get_name() const {
    return name_;
  }

  bool is_constant() const {
    return constant_;
  }

  friend std::ostream &operator<<(std::ostream &os, const Term &term) {
    os << term.name_;
    return os;
  }

  bool operator==(const Term &rhs) const {
    return constant_ == rhs.constant_ &&
           name_ == rhs.name_;
  }

  bool operator!=(const Term &rhs) const {
    return !(rhs == *this);
  }

  bool operator<(const Term &rhs) const {
    if (constant_ != rhs.constant_)
      return constant_;
    return name_ < rhs.name_;
  }

  bool operator>(const Term &rhs) const {
    return rhs < *this;
  }

  bool operator<=(const Term &rhs) const {
    return !(rhs < *this);
  }

  bool operator>=(const Term &rhs) const {
    return !(*this < rhs);
  }

protected:
  static const char kVariableErrorMessage[];
  static const char kConstantErrorMessage[];
  bool constant_;
  std::string name_;

  // Validates name of the term based on its defined name regex
  // Throws an invalid_argument exception with message describing expected name format
  void set_name(const std::string &name, const std::string &name_regex,
                const std::string invalid_name_message) {
    if (std::regex_match(name, std::regex(name_regex))) {
      Term::name_ = name;
    } else {
      throw std::invalid_argument(
          invalid_name_message + ", not like \'" + name + "\'");
    }
  }
};

#endif //HOMEWORK3_SRC_TERM_H
