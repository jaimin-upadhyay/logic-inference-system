//
// Created by Jaimin Upadhyay on 11/14/2016.
//

#ifndef HOMEWORK3_SRC_PREDICATE_H
#define HOMEWORK3_SRC_PREDICATE_H

#include <iostream>
#include <vector>
#include "term.h"

// Defines a predicate which describes some property of its arguments
// A predicate name is a case-sensitive alphabetical string beginning with an uppercase letter
// It takes at least one argument
class Predicate : public std::vector<Term> {
public:
  static const char kRegex[];

  Predicate(const std::string &input_string);

  Predicate(const std::string &name,
            const std::vector<Term> &arguments) {
    set_name(name);
    set_arguments(arguments);
  }

  virtual std::string to_string() const {
    std::ostringstream predicate_string_stream;
    predicate_string_stream << *this;
    return predicate_string_stream.str();
  }

  const std::string &get_name() const {
    return name_;
  }

  // Validates the name of the predicate to be a case-sensitive alphabetical string that begins with an uppercase letter
  void set_name(const std::string &name) {
    if (std::regex_match(name, std::regex("[A-Z][a-zA-Z]*"))) {
      Predicate::name_ = name;
    } else {
      throw std::invalid_argument(
          "Predicate should be a case-sensitive alphabetical string");
    }
  }

  // Validates the number of arguments to the predicate to be at least one
  void set_arguments(const std::vector<Term> &arguments) {
    if (!arguments.empty()) {
      clear();
      for (std::vector<Term>::const_iterator it = arguments.begin();
           it != arguments.end(); it++) {
        push_back(*it);
      }
    } else {
      throw std::invalid_argument(
          "Predicate should have at least one argument");
    }
  }

  friend std::ostream &
  operator<<(std::ostream &os, const Predicate &predicate) {
    os << predicate.name_ << "("
       << predicate.front().to_string();
    for (int i = 1; i < predicate.size(); i++) {
      os << "," << predicate[i].to_string();
    }
    os << ")";
    return os;
  }

  bool operator==(const Predicate &rhs) const {
    return name_ == rhs.name_ &&
           static_cast<const std::vector<Term> &>(*this) ==
           static_cast<const std::vector<Term> &>(rhs);
  }

  bool operator!=(const Predicate &rhs) const {
    return !(rhs == *this);
  }

  bool operator<(const Predicate &rhs) const {
    if (name_ == rhs.name_) {
      return static_cast<const std::vector<Term> &>(*this) <
             static_cast<const std::vector<Term> &>(rhs);
    }
    return name_ < rhs.name_;
  }

  bool operator>(const Predicate &rhs) const {
    return rhs < *this;
  }

  bool operator<=(const Predicate &rhs) const {
    return !(rhs < *this);
  }

  bool operator>=(const Predicate &rhs) const {
    return !(*this < rhs);
  }

protected:
  std::string name_;
};

#endif //HOMEWORK3_SRC_PREDICATE_H
