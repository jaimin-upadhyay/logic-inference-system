//
// Created by Jaimin Upadhyay on 11/19/2016.
//

#ifndef HOMEWORK3_SRC_KNOWLEDGE_BASE_H
#define HOMEWORK3_SRC_KNOWLEDGE_BASE_H

#include <iostream>
#include <vector>
#include <set>
#include <fstream>

#include "sentence.h"
#include "multi_node.h"
#include "knowledge_base_index.h"
#include "output.h"

// Encapsulates all known facts assuming that there are no contradictions in the input.
class KnowledgeBase {
public:
  typedef std::set<Literal> LiteralSet;
  typedef std::map<Term, Term> Theta;

  static void
  Query(const std::string &input_file_name,
        const std::string &output_file_name);

  // Parses a sentence expression string to extract and store sentence parts connected by conjunction.
  void ParseSentenceExpression(std::string input_string) {
    Sentence new_sentence(input_string);
    std::vector<std::set<Literal>> part_sentences;
    new_sentence.GetPartSentences(part_sentences);
    for (std::set<Literal> &part_sentence_literals:part_sentences) {
      AddSentence(part_sentence_literals);
    }
  }

  bool CanResolve(const std::set<Literal> &literal_set);

  bool Ask(Literal query) {
    query.negate();
    bool is_true = CanResolve(LiteralSet({query}));
    resolved_sets_.clear();
    return is_true;
  }

  bool Ask(LiteralSet query_literal_set) {
    bool is_true = true;
    for (LiteralSet::iterator it = query_literal_set.begin();
         it != query_literal_set.end(); it++) {
      if (!Ask(*it)) {
        is_true = false;
        break;
      }
    }
    return is_true;
  }

  std::string to_string() const {
    std::ostringstream kb_ostring_stream;
    operator<<(kb_ostring_stream, *this);
    return kb_ostring_stream.str();
  }

  friend std::ostream &
  operator<<(std::ostream &os, const KnowledgeBase &knowledge_base) {
    os << "{\n" << knowledge_base.store_;
    os << "\n" << knowledge_base.index_ << "\n}\n";
    return os;
  }

protected:
  std::tuple<KnowledgeBase, std::vector<Literal>>
  ReadFromFile(const std::string &file_name);


  std::vector<Literal> ReadQueries(std::ifstream &input_stream);

  KnowledgeBase ReadKnowledgeBase(std::ifstream &input_stream);

  static std::string GetTrimmedLine(std::istream &input_stream);

  bool
  GetTheta(bool change_to_match, const Literal &focus_literal,
           const Literal &match_literal,
           std::map<Term, Term> &theta) const;

  bool Unify(LiteralSet &focus_set_1,
             LiteralSet &focus_set_2,
             const Literal &required_literal,
             const Literal &found_literal) const;

  bool Unify(LiteralSet &focus_set, Theta &theta) const;

  // Updates indexes for all literals in a sentence before storing the sentence.
  void AddSentence(std::set<Literal> &sentence_literals) {
    unsigned long sentence_index = store_.size();
    for (const Literal &sentence_literal:sentence_literals) {
      index_.AddLiteralToIndex(sentence_literal, sentence_index);
    }
    store_.push_back(sentence_literals);
  }

  KnowledgeBaseIndex index_;
  std::vector<std::set<Literal>> store_;
  std::map<LiteralSet, bool> resolved_sets_;
};

#endif //HOMEWORK3_SRC_KNOWLEDGE_BASE_H
