//
// Created by Jaimin Upadhyay on 11/19/2016.
//

#ifndef HOMEWORK3_SRC_SENTENCE_H
#define HOMEWORK3_SRC_SENTENCE_H

#include <iostream>
#include <exception>

#include "term.h"
#include "predicate.h"
#include "literal.h"
#include "node.h"

class Sentence {
public:
  enum Operator {
    kAnd = '&', kOr = '|'
  };

  class LiteralNode : public Literal, public LeafNode {
  public:
    LiteralNode(const Literal &literal) : Literal(literal) {}

    LiteralNode(const Predicate &predicate, bool negation = false) : Literal(
        negation,
        predicate) {}

    void negate() {
      set_negation(!is_negation());
    }

    std::string to_string() const override {
      std::ostringstream literal_node_stream;
      literal_node_stream << *this;
      return literal_node_stream.str();
    }

    std::string get_data_string() const override {
      return to_string();
    }

    Node *copy() const override {
      return new LiteralNode(*this);
    }

    friend std::ostream &operator<<(std::ostream &os, const LiteralNode &node) {
      os << static_cast<const Literal &>(node);
      return os;
    }
  };

  class OperatorNode : public Node {
  public:
    OperatorNode(const char operator_char, Node *left_value,
                 Node *right_value) {
      if (operator_char == kAnd) {
        operator_ = kAnd;
      } else if (operator_char == kOr) {
        operator_ = kOr;
      } else {
        throw std::invalid_argument("Invalid operator: " + operator_char);
      }
      EnsureConjunctiveNormalFormal(left_value, right_value);
    }

    OperatorNode(const OperatorNode &operator_node) : OperatorNode(
        operator_node.get_operator(), operator_node.get_left()->copy(),
        operator_node.get_right()->copy()) {}

    void EnsureConjunctiveNormalFormal(Node *left_value, Node *right_value) {
      if (operator_ == kOr) {
        Node *new_left_value = nullptr, *new_right_value = nullptr;
        // Maintaining Conjunctive Normal Form by distributing OR over AND.
        if (left_value->get_data_string()[0] == kAnd) {
          // Distributive property used: (A & B) | C <=> (A | C) & (B | C)
          operator_ = kAnd;
          new_left_value = new OperatorNode(kOr, left_value->get_left(),
                                            right_value->copy());
          new_right_value = new OperatorNode(kOr, left_value->get_right(),
                                             right_value);
          left_value = new_left_value;
          right_value = new_right_value;
        } else if (right_value->get_data_string()[0] == kAnd) {
          // Distributive property used: A | (B & C) <=> (A | B) & (A | C)
          operator_ = kAnd;
          new_left_value = new OperatorNode(kOr, left_value->copy(),
                                            right_value->get_left());
          new_right_value = new OperatorNode(kOr, left_value,
                                             right_value->get_right());
          left_value = new_left_value;
          right_value = new_right_value;
        }
      }
      set_left(left_value);
      set_right(right_value);
    }

    void negate() {
      if (operator_ == kAnd) {
        operator_ = kOr;
      } else {
        operator_ = kAnd;
      }
      if (left_ != nullptr) {
        left_->negate();
      }
      if (right_ != nullptr) {
        right_->negate();
      }
      EnsureConjunctiveNormalFormal(left_, right_);
    }

    std::string to_string() const override {
      std::ostringstream operator_node_string_stream;
      operator_node_string_stream << *this;
      return operator_node_string_stream.str();
    }

    std::string get_data_string() const override {
      return (operator_ == kAnd ? "&" : "|");
    }

    Node *copy() const override {
      return new OperatorNode(*this);
    }

    Operator get_operator() const {
      return operator_;
    }

    void set_left(Node *left_value) override {
      if (left_value != nullptr) {
        Node::set_left(left_value);
      } else {
        throw std::invalid_argument("Operator left value cannot be undefined");
      }
    }

    void set_right(Node *right_value) override {
      if (right_value != nullptr) {
        Node::set_right(right_value);
      } else {
        throw std::invalid_argument("Operator right value cannot be undefined");
      }
    }

    friend std::ostream &
    operator<<(std::ostream &os, const OperatorNode &node) {
      os << " (" << *node.left_ << (node.operator_ == kAnd ? "&" : "|") <<
         *node.right_ << ") ";
      return os;
    }

  protected:
    Operator operator_;
  };

  Sentence(const std::string &input_string) {
    root_ = ParseSentence(input_string);
  }

  Sentence(const Sentence &sentence) {
    root_ = sentence.root_->copy();
  }

  virtual ~Sentence() {
    if (root_ != nullptr) {
      delete root_;
      root_ = nullptr;
    }
  }

  void
  GetPartSentences(std::vector<std::set<Literal>> &part_sentences) const;


  std::string to_string() const {
    if (root_ != nullptr) {
      return root_->to_string();
    } else {
      return "";
    }
  }

  friend std::ostream &operator<<(std::ostream &os, const Sentence &sentence) {
    os << sentence.to_string();
    return os;
  }

  bool operator==(const Sentence &rhs) const {
    return to_string() == rhs.to_string();
  }

  bool operator!=(const Sentence &rhs) const {
    return !(rhs == *this);
  }

  bool operator<(const Sentence &rhs) const {
    return root_ < rhs.root_;
  }

  bool operator>(const Sentence &rhs) const {
    return rhs < *this;
  }

  bool operator<=(const Sentence &rhs) const {
    return !(rhs < *this);
  }

  bool operator>=(const Sentence &rhs) const {
    return !(*this < rhs);
  }

protected:
  static const char kSymbol[]; // Stores valid symbols.
  static const unsigned int kNumberOfSymbols, kOpeningParenthesisIndex, kImpliesFirstIndex, kImpliesSecondIndex, kOrIndex, kAndIndex, kNotIndex, kClosingParenthesisIndex;
  Node *root_ = nullptr;

  Node *ParseSentence(const std::string &input_string);

  void ConsumeOperator(std::vector<char> &operator_stack,
                       std::vector<Node *> &operand_stack,
                       std::invalid_argument fail_exception);

  template<typename T>
  static T
  PopAndGet(std::vector<T> &stack, std::invalid_argument fail_exception);

  void GetLiterals(Node *traverse_root, std::set<Literal> &literals) const;
};

#endif //HOMEWORK3_SRC_SENTENCE_H
