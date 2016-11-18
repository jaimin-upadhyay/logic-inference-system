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
  const std::string &get_name() const {
    return name_;
  }

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

  bool operator==(const Term &rhs) const {
    return name_ == rhs.name_;
  }

  bool operator!=(const Term &rhs) const {
    return !(rhs == *this);
  }

  bool operator<(const Term &rhs) const {
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
  Term(const std::string &name, const std::string &name_regex,
       const std::string invalid_name_message) {
    set_name(name, name_regex, invalid_name_message);
  }

  std::string name_;
};

// Defines a constant which is a term whose name has to be a case-sensitive alphabetical string beginning with an uppercase letter
class Constant : public Term {
public:
  static const char kRegex[];

  Constant(const std::string &name) : Term(name, kRegex,
                                           "Constants be a case-sensitive alphabetical string beginning with a upper case letter") {
  }
};

// Defines a variable which is a term which can take a value and whose name is a single lower case letter
class Variable : public Term {
public:
  static const char kRegex[];

  Variable(const std::string &name) : Variable(name, nullptr) {}

  Variable(const std::string &name, Constant *value) : Term(name, kRegex,
                                                            "Variables should be a single lower case letter"),
                                                       value_(value) {
  }

  std::string get_value() const {
    return value_ ? value_->get_name() : name_;
  }

  void set_value(Constant *value) {
    Variable::value_ = value;
  }

  // Returns true when no constant has been assigned to the variable
  // i.e. when the pointer to constant is equal to nullptr.
  bool is_assigned() {
    return value_ != nullptr;
  }

  bool operator==(const Variable &rhs) const {
    return static_cast<const Term &>(*this) == static_cast<const Term &>(rhs) &&
           value_ == rhs.value_;
  }

  bool operator!=(const Variable &rhs) const {
    return !(rhs == *this);
  }

  bool operator<(const Variable &rhs) const {
    if (static_cast<const Term &>(*this) < static_cast<const Term &>(rhs))
      return true;
    if (static_cast<const Term &>(rhs) < static_cast<const Term &>(*this))
      return false;
    return value_ < rhs.value_;
  }

  bool operator>(const Variable &rhs) const {
    return rhs < *this;
  }

  bool operator<=(const Variable &rhs) const {
    return !(rhs < *this);
  }

  bool operator>=(const Variable &rhs) const {
    return !(*this < rhs);
  }

protected:
  Constant *value_;
};

#endif //HOMEWORK3_SRC_TERM_H
