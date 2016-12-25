//
// Created by Jaimin Upadhyay on 11/29/2016.
//

#ifndef HOMEWORK3_SRC_KNOWLEDGE_BASE_INDEX_H
#define HOMEWORK3_SRC_KNOWLEDGE_BASE_INDEX_H

#include <iostream>
#include <vector>
#include <utility>

#include "output.h"
#include "sentence.h"
#include "multi_node.h"

class KnowledgeBaseIndex {
public:
  class ArgumentEntry : public Term {
  public:
    ArgumentEntry(const Term &argument, MultiNode *next_node) : Term(
        argument), next_node(next_node) {}

    MultiNode *get_next_node() const {
      return next_node;
    }

    void set_next_node(MultiNode *next_node) {
      ArgumentEntry::next_node = next_node;
    }

    friend std::ostream &
    operator<<(std::ostream &os, const ArgumentEntry &entry) {
      os << static_cast<Term>(entry) << " : " << entry.next_node;
      return os;
    }

  protected:
    MultiNode *next_node;
  };

  class ArgumentIndexNode : public MultiNode {
  public:
    typedef std::map<Term, MultiNode *> ConstantIndex;
    typedef std::list<ArgumentEntry> VariableIndex;

    ArgumentIndexNode() : unifiable_variable_index_iterator_(
        variable_index_.end()),
                          unifiable_constant_index_iterator_(
                              constant_index_.end()) {
    }

    MultiNode *get_next_constant_node(const Term &term) {
      ConstantIndex::iterator constant_iterator = constant_index_.find(term);
      if (constant_iterator != constant_index_.end()) {
        return constant_iterator->second;
      }
      return nullptr;
    }

    MultiNode *get_next_variable_node(const Term &term) {
      VariableIndex::iterator it = variable_index_.begin();
      for (; it != variable_index_.end(); it++) {
        if (*it == term) {
          return it->get_next_node();
        }
      }
      return nullptr;
    }

    MultiNode *get_next_node(const Term &term) {
      if (term.is_constant()) {
        return get_next_constant_node(term);
      }
      return get_next_variable_node(term);
    }

    MultiNode *get_unifiable_next_node(const Term &term) {
      if (term.is_constant()) {
        MultiNode *next_constant_node = get_next_constant_node(term);
        if (next_constant_node != nullptr) {
          return next_constant_node;
        }
      }
      return get_unifiable_variable_node(term);
    }

    MultiNode *get_unifiable_variable_node(const Term &term) {
      if (!variable_index_.empty()) {
        if (unifiable_variable_index_iterator_ == variable_index_.end()) {
          unifiable_variable_index_iterator_ = variable_index_.begin();
          if (!term.is_constant() && !constant_index_.empty()) {
            return get_unifiable_constant_node(term);
          }
        }
        MultiNode *unifiable_variable_node = unifiable_variable_index_iterator_->get_next_node();
        unifiable_variable_index_iterator_++;
        return unifiable_variable_node;
      }
      return get_unifiable_constant_node(term);
    }

    MultiNode *get_unifiable_constant_node(const Term &term) {
      if (!term.is_constant()) {
        if (!constant_index_.empty()) {
          if (unifiable_constant_index_iterator_ == constant_index_.end()) {
            unifiable_constant_index_iterator_ = constant_index_.begin();
          }
          MultiNode *unifiable_constant_node = unifiable_constant_index_iterator_->second;
          unifiable_constant_index_iterator_++;
          return unifiable_constant_node;
        } else if (!variable_index_.empty()) {
          return get_unifiable_variable_node(term);
        }
      }
      return nullptr;
    }

    MultiNode *set_next_node(Term term, MultiNode *term_next_node) {
      if (!term.is_constant()) {
        variable_index_.push_back(ArgumentEntry(term, term_next_node));
        if (unifiable_variable_index_iterator_ == variable_index_.end()) {
          unifiable_variable_index_iterator_ = variable_index_.begin();
        }
      } else {
        constant_index_[term] = term_next_node;
        if (unifiable_constant_index_iterator_ == constant_index_.end()) {
          unifiable_constant_index_iterator_ = constant_index_.begin();
        }
      }
    }

    std::string constant_to_string() const {
      std::ostringstream constant_string_stream;
      ConstantIndex::const_iterator constant_iterator = constant_index_.begin();
      if (constant_iterator == constant_index_.end()) {
        constant_string_stream << "nullptr";
      } else {
        constant_string_stream << "[ ";
        constant_string_stream << constant_iterator->first << ": ";
        if (constant_iterator->second != nullptr) {
          constant_string_stream << *(constant_iterator->second);
        } else {
          constant_string_stream << "nullptr";
        }
        for (constant_iterator++;
             constant_iterator != constant_index_.end(); constant_iterator++) {
          constant_string_stream << ", " << constant_iterator->first << ": ";
          if (constant_iterator->second != nullptr) {
            constant_string_stream << *(constant_iterator->second);
          } else {
            constant_string_stream << "nullptr";
          }
        }
        constant_string_stream << " ]";
      }
      return constant_string_stream.str();
    }

    std::string variable_to_string() const {
      std::ostringstream variable_string_stream;
      VariableIndex::const_iterator variable_iterator = variable_index_.begin();
      if (variable_iterator == variable_index_.end()) {
        variable_string_stream << "nullptr";
      } else {
        variable_string_stream << "[" << static_cast<Term>(*variable_iterator);
        variable_string_stream << " : "
                               << *(variable_iterator->get_next_node());
        for (variable_iterator++; variable_iterator !=
                                  variable_index_.end(); variable_iterator++) {
          variable_string_stream << ", "
                                 << static_cast<Term>(*variable_iterator);
          variable_string_stream << " : "
                                 << *(variable_iterator->get_next_node());
        }
        variable_string_stream << "]";
      }
      return variable_string_stream.str();
    }

    std::string to_string() const override {
      std::ostringstream argument_index_node_string_stream;
      argument_index_node_string_stream << "[ " << "K: " << constant_to_string()
                                        << ", v: " << variable_to_string()
                                        << " ]";
      return argument_index_node_string_stream.str();
    }

  protected:
    ConstantIndex constant_index_;
    VariableIndex variable_index_;
    VariableIndex::iterator unifiable_variable_index_iterator_;
    ConstantIndex::iterator unifiable_constant_index_iterator_;
  };

  class LiteralEntry {
  public:
    LiteralEntry() : LiteralEntry(nullptr, nullptr) {}

    LiteralEntry(ArgumentIndexNode *negative, ArgumentIndexNode *positive)
        : negative_(
        negative), positive_(positive) {}

    ArgumentIndexNode *get_negative() {
      return negative_;
    }

    void set_negative(ArgumentIndexNode *negative) {
      negative_ = negative;
    }

    ArgumentIndexNode *get_positive() {
      return positive_;
    }

    void set_positive(ArgumentIndexNode *positive) {
      positive_ = positive;
    }

    friend std::ostream &
    operator<<(std::ostream &os, const LiteralEntry &index) {
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

  class SentenceEntry {
  public:
    SentenceEntry(unsigned long sentence_index, Literal literal)
        : sentence_index_(sentence_index), literal_(literal) {}

    unsigned long get_index() const {
      return sentence_index_;
    }

    void set_index(unsigned long sentence_index) {
      sentence_index_ = sentence_index;
    }

    const Literal &get_literal() const {
      return literal_;
    }

    void set_literal(const Literal &literal) {
      literal_ = literal;
    }

    bool operator==(const SentenceEntry &rhs) const {
      return sentence_index_ == rhs.sentence_index_ && literal_ == rhs.literal_;
    }

    bool operator!=(const SentenceEntry &rhs) const {
      return !(rhs == *this);
    }

    bool operator<(const SentenceEntry &rhs) const {
      return literal_ < rhs.literal_ || sentence_index_ < rhs.sentence_index_;
    }

    bool operator>(const SentenceEntry &rhs) const {
      return rhs < *this;
    }

    bool operator<=(const SentenceEntry &rhs) const {
      return !(rhs < *this);
    }

    bool operator>=(const SentenceEntry &rhs) const {
      return !(*this < rhs);
    }

    friend std::ostream &
    operator<<(std::ostream &os, const SentenceEntry &index) {
      os << index.sentence_index_;
      return os;
    }

  protected:
    unsigned long sentence_index_;
    Literal literal_;
  };

  class SentenceIndexNode : public ListMultiNode<SentenceEntry> {
  public:
    SentenceIndexNode() : next_sentence_iterator_(end()) {}

    void insert(SentenceEntry sentence_entry) {
      push_back(sentence_entry);
      next_sentence_iterator_ = begin();
    }

    SentenceEntry *get_next_sentence_entry() {
      SentenceEntry *next_sentence_entry = nullptr;
      if (next_sentence_iterator_ == end()) {
        next_sentence_iterator_ = begin();
      }
      next_sentence_entry = &(*next_sentence_iterator_);
      next_sentence_iterator_++;
      return next_sentence_entry;
    }


  protected:
    iterator next_sentence_iterator_;
  };

  friend std::ostream &
  operator<<(std::ostream &os,
             const KnowledgeBaseIndex &knowledge_base_index) {
    os << "[\n";
    for (std::map<std::string, LiteralEntry>::const_iterator it = knowledge_base_index.index_map.begin();
         it != knowledge_base_index.index_map.end(); it++) {
      os << "\t" << it->first << ": " << it->second << "\n";
    }
    os << "]";
    return os;
  }

  // Adds a given literal to the index tree.
  void
  AddLiteralToIndex(Literal literal,
                    unsigned long sentence_index) {
    std::string literal_name = literal.get_name();
    std::vector<Term> literal_arguments = literal;
    ArgumentIndexNode *current_argument_index = nullptr;
    MultiNode *next_multi_node = nullptr;
    LiteralEntry &literal_index = index_map[literal_name];
    if (literal.is_negation()) {
      current_argument_index = literal_index.get_negative();
      if (current_argument_index == nullptr) {
        current_argument_index = new ArgumentIndexNode();
        literal_index.set_negative(current_argument_index);
      }
    } else {
      current_argument_index = literal_index.get_positive();
      if (current_argument_index == nullptr) {
        current_argument_index = new ArgumentIndexNode();
        literal_index.set_positive(current_argument_index);
      }
    }
    try {
      for (int i = 0; i < literal_arguments.size() - 1; i++) {
        next_multi_node = current_argument_index->get_next_node(
            literal_arguments[i]);
        if (next_multi_node == nullptr) {
          next_multi_node = new ArgumentIndexNode();
          current_argument_index->set_next_node(literal_arguments[i],
                                                next_multi_node);
        }
        current_argument_index = dynamic_cast<ArgumentIndexNode *>(next_multi_node);
      }
      next_multi_node = current_argument_index->get_next_node(
          literal_arguments.back());
      if (next_multi_node == nullptr) {
        next_multi_node = new SentenceIndexNode();
        current_argument_index->set_next_node(literal_arguments.back(),
                                              next_multi_node);
      }
      SentenceIndexNode *
          sentence_index_node = dynamic_cast<SentenceIndexNode *>(next_multi_node);
      sentence_index_node->insert(SentenceEntry(sentence_index, literal));
    } catch (std::bad_cast bad_cast_exception) {
      throw std::invalid_argument("Invalid literal for the knowledge base");
    }
  }

  SentenceEntry *GetSentenceIndexes(const Literal &literal) {
    SentenceIndexNode *sentence_index_node = GetSentenceIndexNode(literal);
    return sentence_index_node == nullptr ? nullptr
                                          : sentence_index_node->get_next_sentence_entry();
  }

  SentenceIndexNode *GetSentenceIndexNode(const Literal &literal) {
    SentenceIndexNode *sentence_index_node = nullptr;
    ArgumentIndexNode *current_argument_index_node = nullptr;
    MultiNode *next_multi_node = nullptr;
    LiteralEntry &literal_index = index_map[literal.get_name()];
    if (literal.is_negation()) {
      current_argument_index_node = literal_index.get_negative();
    } else {
      current_argument_index_node = literal_index.get_positive();
    }
    if (current_argument_index_node != nullptr) {
      try {
        for (int i = 0; i < literal.size() - 1; i++) {
          next_multi_node = current_argument_index_node->get_unifiable_next_node(
              literal[i]);
          current_argument_index_node = dynamic_cast<ArgumentIndexNode *>(next_multi_node);
        }
        if (current_argument_index_node != nullptr) {
          next_multi_node = current_argument_index_node->get_unifiable_next_node(
              literal.back());
          if (next_multi_node != nullptr) {
            sentence_index_node = dynamic_cast<SentenceIndexNode *>(next_multi_node);
          }
        }
      } catch (std::bad_cast
               bad_cast_exception) {
        throw std::invalid_argument("Invalid literal for the knowledge base");
      }
    }
    return sentence_index_node;
  }

protected:
  std::map<std::string, LiteralEntry> index_map;
};

#endif //HOMEWORK3_SRC_KNOWLEDGE_BASE_INDEX_H
