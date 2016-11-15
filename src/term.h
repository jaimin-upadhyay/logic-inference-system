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
protected:
  std::string name_;
  std::regex name_regex_;
  std::string invalid_name_message_;

  Term(const std::string &name, const std::string &name_regex_string,
       const std::string &invalid_name_message);

public:
  Term(const std::string &name) : Term(name, ".*", "") {
  }

  const std::string &get_name() const {
    return name_;
  }

  // Validates name of the term based on its defined name regex
  // Throws an invalid_argument exception with message describing expected name format
  void set_name(const std::string &name) {
    if (std::regex_match(name, name_regex_)) {
      Term::name_ = name;
    } else {
      throw std::invalid_argument(
          invalid_name_message_ + ", not like \'" + name + "\'");
    }
  }
};

// Defines a constant which is a term whose name has to be a case-sensitive alphabetical string beginning with an uppercase letter
class Constant : public Term {
public:
  Constant(const std::string &name) : Term(name, "[A-Z][a-zA-Z]*",
                                           "Constant name should be a case-sensitive alphabetical string that begins with an uppercase letter") {
  }
};

// Defines a variable which is a term which can take a value and whose name is a single lower case letter
class Variable : public Term {
protected:
  Constant *value_;
public:
  Variable(const std::string &name) : Variable(name, nullptr) {}

  Variable(const std::string &name, Constant *value) : Term(name,
                                                            "[a-z]",
                                                            "Variable name should be a single lower case letter"),
                                                       value_(value) {
  }

  Constant *get_value() const {
    return value_;
  }

  void set_value(Constant *value) {
    Variable::value_ = value;
  }

  // Returns true when no constant has been assigned to the variable
  // i.e. when the pointer to constant is equal to nullptr.
  bool is_assigned() {
    return value_ != nullptr;
  }
};

#endif //HOMEWORK3_SRC_TERM_H
