//
// Created by Jaimin Upadhyay on 11/19/2016.
//

#ifndef HOMEWORK3_SRC_SENTENCE_H
#define HOMEWORK3_SRC_SENTENCE_H

#include <iostream>
#include <exception>

#include "term.h"
#include "predicate.h"

class Sentence {
public:
  enum Operator {
    kAnd = '&', kOr = '|'
  };

  class Node {
  public:
    Node() : left_(nullptr), right_(nullptr) {}

    Node(Node *left_, Node *right_) : left_(left_), right_(right_) {}

    virtual ~Node() {
      if (left_ != nullptr) {
        delete left_;
        left_ = nullptr;
      }
      if (right_ != nullptr) {
        delete right_;
        right_ = nullptr;
      }
    }

    virtual Node *copy() const = 0;

    virtual std::string get_data_string() const = 0;

    virtual Node *get_left() const {
      return left_;
    }

    virtual void set_left(Node *left) {
      Node::left_ = left;
    }

    virtual Node *get_right() const {
      return right_;
    };

    virtual void set_right(Node *right) {
      Node::right_ = right;
    }

    virtual void negate() = 0;

    virtual std::string to_string() const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Node &node) {
      os << node.to_string();
      return os;
    }

  protected:
    Node *left_, *right_;
  };

  class LeafNode : public Node {
  public:
    class LeafException : public std::runtime_error {
    public:
      LeafException() : runtime_error("Leaf nodes do not have children") {}
    };

    virtual Node *get_left() const override {
      handle_child_operations();
    }

    virtual void set_left(Node *left) override {
      handle_child_operations();
    }

    virtual Node *get_right() const override {
      handle_child_operations();
    }

    virtual void set_right(Node *right) override {
      handle_child_operations();
    }

    void handle_child_operations() const {
      throw LeafException();
    }
  };

  class PredicateNode : public LeafNode {
  public:
    PredicateNode(const Predicate &predicate_) : PredicateNode(predicate_,
                                                               false) {}

    PredicateNode(const Predicate &predicate_, bool negation_) : predicate_(
        predicate_), negation_(negation_) {}

    void negate() {
      set_negation(!is_negation());
    }

    std::string to_string() const override {
      return (is_negation() ? " ~" : " ") + predicate_.to_string() + " ";
    }


    std::string get_data_string() const override {
      return to_string();
    }

    Node *copy() const override {
      return new PredicateNode(*this);
    }

    bool is_negation() const {
      return negation_;
    }

    void set_negation(bool negation) {
      PredicateNode::negation_ = negation;
    }

    const Predicate &get_predicate() const {
      return predicate_;
    }


    void set_predicate(const Predicate &predicate) {
      PredicateNode::predicate_ = predicate;
    }

  protected:
    bool negation_;
    Predicate predicate_;
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
    }

    std::string to_string() const override {
      return " (" + left_->to_string() + (operator_ == kAnd ? "&" : "|") +
             right_->to_string() + ") ";
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

    void set_operator(Operator operator_) {
      OperatorNode::operator_ = operator_;
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

  protected:
    Operator operator_;
  };

  Sentence(Node *root) : root_(root) {}

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
};


#endif //HOMEWORK3_SRC_SENTENCE_H
