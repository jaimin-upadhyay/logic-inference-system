//
// Created by Jaimin Upadhyay on 11/19/2016.
//

#ifndef HOMEWORK3_SRC_KNOWLEDGE_BASE_H
#define HOMEWORK3_SRC_KNOWLEDGE_BASE_H

#include <iostream>
#include <vector>

#include "sentence.h"
#include "output.h"

// Encapsulates all know facts assuming that there are no contradictions in the input.
class KnowledgeBase {
public:

  // Base class for nodes with multiple values.
  class MultiNode {
  public:
    virtual ~MultiNode() {};

    virtual std::string to_string() const =0;

    friend std::ostream &
    operator<<(std::ostream &os, const MultiNode &node) {
      os << node.to_string();
      return os;
    }
  };

  // Node using a hash map to store multiple values.
  template<typename K, typename V>
  class MapMultiNode : public std::map<K, V *>, public MultiNode {
  public:
    virtual ~MapMultiNode() {
      typename MapMultiNode::iterator map_iterator = MapMultiNode::begin();
      while (map_iterator != MapMultiNode::end()) {
        if (map_iterator->second != nullptr) {
          delete map_iterator->second;
          map_iterator->second = nullptr;
        }
        map_iterator++;
      }
    }

    std::string to_string() const override {
      std::ostringstream node_string_stream;
      typename MapMultiNode::const_iterator map_iterator = MapMultiNode::begin();
      node_string_stream << "[ ";
      node_string_stream << map_iterator->first << ": ";
      if (map_iterator->second != nullptr) {
        node_string_stream << *(map_iterator->second);
      } else {
        node_string_stream << "nullptr";
      }
      for (map_iterator++;
           map_iterator != MapMultiNode::end(); map_iterator++) {
        node_string_stream << ", " << map_iterator->first << ": ";
        if (map_iterator->second != nullptr) {
          node_string_stream << *(map_iterator->second);
        } else {
          node_string_stream << "nullptr";
        }
      }
      node_string_stream << " ]";
      return node_string_stream.str();
    }

    friend std::ostream &
    operator<<(std::ostream &os, const MapMultiNode<K, V> &node) {
      os << node.to_string();
      return os;
    }
  };

  // Node which uses a vector to store multiple values.
  template<typename T>
  class VectorMultiNode : public std::vector<T>, public MultiNode {
  public:
    std::string to_string() const override {
      std::ostringstream node_string_stream;
      node_string_stream << "[";
      copy(VectorMultiNode::begin(), VectorMultiNode::end() - 1,
           std::ostream_iterator<T>(node_string_stream, ", "));
      node_string_stream << VectorMultiNode::back() << "]";
      return node_string_stream.str();
    }

    friend std::ostream &
    operator<<(std::ostream &output_stream, const VectorMultiNode &node) {
      output_stream << node.to_string();
      return output_stream;
    }
  };

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

  // Parses a sentence expression string to extract and store sentence parts connected by conjunction.
  void ParseSentenceExpression(std::string input_string) {
    Sentence new_sentence(input_string);
    std::vector<Sentence> part_sentences;
    new_sentence.GetPartSentences(part_sentences);
    for (Sentence &part_sentence:part_sentences) {
      AddSentence(part_sentence);
    }
  }

  unsigned int size() {
    return sentences_.size();
  }

  Sentence operator[](int i) {
    return sentences_[i];
  }

  friend std::ostream &
  operator<<(std::ostream &os, const KnowledgeBase &knowledge_base) {
    os << "Sentences: " << knowledge_base.sentences_ << std::endl;
    os << "Index {\n";
    for (std::map<std::string, LiteralIndex>::const_iterator it = knowledge_base.index_.begin();
         it != knowledge_base.index_.end(); it++) {
      os << "\t" << it->first << ": " << it->second << std::endl;
    }
    os << " }\n";
    return os;
  }

protected:
  // Adds a given literal to the index tree.
  void AddLiteralToIndex(Literal &literal, unsigned int sentence_index) {
    std::string literal_name = literal.get_predicate().get_name();
    std::vector<Term> literal_arguments = literal.get_predicate().get_arguments();
    ArgumentIndexNode *current_argument_index = nullptr;
    MultiNode *next_multi_node = nullptr;
    LiteralIndex &literal_index = index_[literal_name];
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

  // Updates indexes for all literals in a sentence before storing the sentence.
  void AddSentence(Sentence &sentence) {
    std::vector<Literal> sentence_literals;
    sentence.GetLiterals(sentence_literals);
    unsigned int sentence_index = sentences_.size();
    for (Literal &sentence_literal:sentence_literals) {
      AddLiteralToIndex(sentence_literal, sentence_index);
    }
    sentences_.push_back(sentence);
  }

  std::vector<Sentence> sentences_;
  std::map<std::string, LiteralIndex> index_;
};

#endif //HOMEWORK3_SRC_KNOWLEDGE_BASE_H
