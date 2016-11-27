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
class Predicate {
public:
  static const char kRegex[];

  Predicate(const std::string &input_string);

  Predicate(const std::string &name,
            const std::vector<Term> &arguments) {
    set_name(name);
    set_arguments(arguments);
  }

  void AddArgument(std::string input_string);

  std::string to_string() const;

  const std::string &get_name() const {
    return name_;
  }

  void set_name(const std::string &name);

  const std::vector<Term> &get_arguments() const {
    return arguments_;
  }

  void set_arguments(const std::vector<Term> &arguments);

  friend std::ostream &operator<<(std::ostream &os, const Predicate &predicate) {
    os << predicate.to_string();
    return os;
  }

  bool operator==(const Predicate &rhs) const {
    return name_ == rhs.name_ &&
           arguments_ == rhs.arguments_;
  }

  bool operator!=(const Predicate &rhs) const {
    return !(rhs == *this);
  }

  bool operator<(const Predicate &rhs) const {
    if (name_ < rhs.name_)
      return true;
    if (rhs.name_ < name_)
      return false;
    return arguments_ < rhs.arguments_;
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
  std::vector<Term> arguments_;
};

#endif //HOMEWORK3_SRC_PREDICATE_H
