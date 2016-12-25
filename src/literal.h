//
// Created by Jaimin Upadhyay on 11/17/2016.
//

#ifndef HOMEWORK3_SRC_QUERY_H
#define HOMEWORK3_SRC_QUERY_H

#include <iostream>
#include "predicate.h"

class Literal : public Predicate {
public:
  // Creates a literal from the input string
  // Language Specification: Initialization of the constructor initializer list is based on the member's declaration order
  Literal(const std::string &input_string) : negation_(input_string[0] == '~'),
                                             Predicate(input_string[0] == '~' ?
                                                       input_string.substr(1) :
                                                       input_string) {
  }

  Literal(bool negation, const Predicate &predicate) : negation_(negation),
                                                       Predicate(predicate) {}

  std::string to_string() const {
    std::ostringstream literal_string_stream;
    literal_string_stream << *this;
    return literal_string_stream.str();
  }

  void negate() {
    set_negation(!is_negation());
  }

  bool is_negation() const {
    return negation_;
  }

  void set_negation(bool negation) {
    Literal::negation_ = negation;
  }

  friend std::ostream &operator<<(std::ostream &os, const Literal &literal) {
    const Predicate *predicate = &literal;
    os << " " << (literal.negation_ ? "~" : "");
    operator<<(os, *predicate);
    os << " ";
    return os;
  }

  bool operator==(const Literal &rhs) const {
    return negation_ == rhs.negation_ &&
           static_cast<const Predicate &>(*this) ==
           static_cast<const Predicate &>(rhs);
  }

  bool operator!=(const Literal &rhs) const {
    return !(rhs == *this);
  }

  bool operator<(const Literal &rhs) const {
    if (static_cast<const Predicate &>(*this) <
        static_cast<const Predicate &>(rhs))
      return true;
    if (static_cast<const Predicate &>(rhs) <
        static_cast<const Predicate &>(*this))
      return false;
    return negation_ < rhs.negation_;
  }

  bool operator>(const Literal &rhs) const {
    return rhs < *this;
  }

  bool operator<=(const Literal &rhs) const {
    return !(rhs < *this);
  }

  bool operator>=(const Literal &rhs) const {
    return !(*this < rhs);
  }

protected:
  bool negation_;
};

#endif //HOMEWORK_3_SRC_QUERY_H
