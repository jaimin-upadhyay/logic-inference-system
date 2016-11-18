//
// Created by Jaimin Upadhyay on 11/17/2016.
//

#ifndef HOMEWORK3_SRC_QUERY_H
#define HOMEWORK3_SRC_QUERY_H

#include <iostream>
#include "predicate.h"

class Query {
public:
  // Creates a query from the input string
  // Note: Initialization of the constructor initializer list is based on the member's declaration order
  Query(const std::string &input_string) : negation(input_string[0] == '~'),
                                           predicate(negation ? input_string.substr(1) : input_string) {
  }

  Query(bool negation, const Predicate &predicate) : negation(negation), predicate(predicate) {}

  std::string to_string() {
    return (negation ? "~" : "") + predicate.to_string();
  }

  bool is_negation() const {
    return negation;
  }

  void set_negation(bool negation) {
    Query::negation = negation;
  }

  const Predicate &get_predicate() const {
    return predicate;
  }

  void set_predicate(const Predicate &predicate) {
    Query::predicate = predicate;
  }

  bool operator==(const Query &rhs) const {
    return negation == rhs.negation &&
           predicate == rhs.predicate;
  }

  bool operator!=(const Query &rhs) const {
    return !(rhs == *this);
  }

  bool operator<(const Query &rhs) const {
    if (negation < rhs.negation)
      return true;
    if (rhs.negation < negation)
      return false;
    return predicate < rhs.predicate;
  }

  bool operator>(const Query &rhs) const {
    return rhs < *this;
  }

  bool operator<=(const Query &rhs) const {
    return !(rhs < *this);
  }

  bool operator>=(const Query &rhs) const {
    return !(*this < rhs);
  }

protected:
  bool negation;
  Predicate predicate;
};

#endif //HOMEWORK_3_SRC_QUERY_H
