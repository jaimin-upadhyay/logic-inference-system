//
// Created by Jaimin Upadhyay on 11/29/2016.
//

#ifndef HOMEWORK3_SRC_NODE_H
#define HOMEWORK3_SRC_NODE_H

#include <iostream>

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
  class LeafException : public std::invalid_argument {
  public:
    LeafException() : invalid_argument("Leaf nodes do not have children") {}
  };

  virtual Node *get_left() const override {
    handle_child_operations();
    return nullptr;
  }

  virtual void set_left(Node *left) override {
    handle_child_operations();
  }

  virtual Node *get_right() const override {
    handle_child_operations();
    return nullptr;
  }

  virtual void set_right(Node *right) override {
    handle_child_operations();
  }

  void handle_child_operations() const {
    throw LeafException();
  }
};

#endif //HOMEWORK3_SRC_NODE_H
