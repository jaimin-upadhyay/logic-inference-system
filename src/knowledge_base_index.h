//
// Created by Jaimin Upadhyay on 11/29/2016.
//

#ifndef HOMEWORK3_SRC_KNOWLEDGE_BASE_INDEX_H
#define HOMEWORK3_SRC_KNOWLEDGE_BASE_INDEX_H

#include <iostream>

#include "sentence.h"
#include "multi_node.h"

class KnowledgeBaseIndex {
public:
  typedef MapMultiNode<Term, MultiNode> ArgumentIndexNode;

  typedef VectorMultiNode<unsigned int> SentenceIndexNode;

  class LiteralIndex {
  public:
    LiteralIndex() : LiteralIndex(nullptr, nullptr) {}

    LiteralIndex(ArgumentIndexNode *negative, ArgumentIndexNode *positive)
        : negative_(
        negative), positive_(positive) {}

    ArgumentIndexNode *get_negative() {
      if (negative_ == nullptr) {
        set_negative(new ArgumentIndexNode());
      }
      return negative_;
    }

    void set_negative(ArgumentIndexNode *negative) {
      negative_ = negative;
    }

    ArgumentIndexNode *get_positive() {
      if (positive_ == nullptr) {
        set_positive(new ArgumentIndexNode());
      }
      return positive_;
    }

    void set_positive(ArgumentIndexNode *positive) {
      positive_ = positive;
    }

    friend std::ostream &
    operator<<(std::ostream &os, const LiteralIndex &index) {
      os << "( - : ";
      if (index.negative_ != nullptr) {
        os << *(index.negative_);
      } else {
        os << "null";
      }
      os << " ) ( + : ";
      if (index.positive_ != nullptr) {
        os << *(index.positive_);
      }
      os << " )";
      return os;
    }

  protected:
    ArgumentIndexNode *negative_, *positive_;
  };

  friend std::ostream &
  operator<<(std::ostream &os, const KnowledgeBaseIndex &knowledge_base_index) {
    os << "[\n";
    for (std::map<std::string, LiteralIndex>::const_iterator it = knowledge_base_index.index_map.begin();
         it != knowledge_base_index.index_map.end(); it++) {
      os << "\t" << it->first << ": " << it->second << "\n";
    }
    os << "]";
    return os;
  }

  // Adds a given literal to the index tree.
  void AddLiteralToIndex(Literal &literal, unsigned int sentence_index) {
    std::string literal_name = literal.get_predicate().get_name();
    std::vector<Term> literal_arguments = literal.get_predicate().get_arguments();
    ArgumentIndexNode *current_argument_index = nullptr;
    MultiNode *next_multi_node = nullptr;
    LiteralIndex &literal_index = index_map[literal_name];
    if (literal.is_negation()) {
      current_argument_index = literal_index.get_negative();
    } else {
      current_argument_index = literal_index.get_positive();
    }
    try {
      for (int i = 0; i < literal_arguments.size() - 1; i++) {
        next_multi_node = (*current_argument_index)[literal_arguments[i]];
        if (next_multi_node == nullptr) {
          next_multi_node = new ArgumentIndexNode();
          (*current_argument_index)[literal_arguments[i]] = next_multi_node;
        }
        current_argument_index = dynamic_cast<ArgumentIndexNode *>(next_multi_node);
      }
      next_multi_node = (*current_argument_index)[literal_arguments.back()];
      if (next_multi_node == nullptr) {
        next_multi_node = new SentenceIndexNode();
        (*current_argument_index)[literal_arguments.back()] = next_multi_node;
      }
      SentenceIndexNode *sentence_index_node = dynamic_cast<SentenceIndexNode *>(next_multi_node);
      sentence_index_node->push_back(sentence_index);
    } catch (std::bad_cast bad_cast_exception) {
      throw std::invalid_argument("Invalid literal for the knowledge base");
    }
  }

protected:
  std::map<std::string, LiteralIndex> index_map;
};

#endif //HOMEWORK3_SRC_KNOWLEDGE_BASE_INDEX_H
