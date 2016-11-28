//
// Created by Jaimin Upadhyay on 11/17/2016.
//

#ifndef HOMEWORK3_SRC_QUERY_H
#define HOMEWORK3_SRC_QUERY_H

#include <iostream>
#include "predicate.h"

class Literal {
public:
  // Creates a literal from the input string
  // Language Specification: Initialization of the constructor initializer list is based on the member's declaration order
  Literal(const std::string &input_string) : negation(input_string[0] == '~'),
                                             predicate(negation ?
                                                       input_string.substr(1) :
                                                       input_string) {
  }

  Literal(bool negation, const Predicate &predicate) : negation(negation),
                                                       predicate(predicate) {}

  std::string to_string() const {
    std::ostringstream literal_string_stream;
    literal_string_stream << " " << (negation ? "~" : "")
                          << predicate.to_string() << " ";
    return literal_string_stream.str();
  }

  bool is_negation() const {
    return negation;
  }

  void set_negation(bool negation) {
    Literal::negation = negation;
  }

  const Predicate &get_predicate() const {
    return predicate;
  }

  void set_predicate(const Predicate &predicate) {
    Literal::predicate = predicate;
  }

  friend std::ostream &operator<<(std::ostream &os, const Literal &literal) {
    return os << literal.to_string();
  }

  bool operator==(const Literal &rhs) const {
    return negation == rhs.negation &&
           predicate == rhs.predicate;
  }

  bool operator!=(const Literal &rhs) const {
    return !(rhs == *this);
  }

  bool operator<(const Literal &rhs) const {
    if (negation < rhs.negation)
      return true;
    if (rhs.negation < negation)
      return false;
    return predicate < rhs.predicate;
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
  bool negation;
  Predicate predicate;
};

#endif //HOMEWORK_3_SRC_QUERY_H
