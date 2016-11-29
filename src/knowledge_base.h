//
// Created by Jaimin Upadhyay on 11/19/2016.
//

#ifndef HOMEWORK3_SRC_KNOWLEDGE_BASE_H
#define HOMEWORK3_SRC_KNOWLEDGE_BASE_H

#include <iostream>
#include <vector>

#include "sentence.h"
#include "output.h"
#include "multi_node.h"
#include "knowledge_base_index.h"

// Encapsulates all know facts assuming that there are no contradictions in the input.
class KnowledgeBase {
public:
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
    os << "{\n" << knowledge_base.sentences_;
    os << "\n" << knowledge_base.index_ << "\n}\n";
    return os;
  }

protected:
  // Updates indexes for all literals in a sentence before storing the sentence.
  void AddSentence(Sentence &sentence) {
    std::vector<Literal> sentence_literals;
    sentence.GetLiterals(sentence_literals);
    unsigned int sentence_index = sentences_.size();
    for (Literal &sentence_literal:sentence_literals) {
      index_.AddLiteralToIndex(sentence_literal, sentence_index);
    }
    sentences_.push_back(sentence);
  }

  KnowledgeBaseIndex index_;
  std::vector<Sentence> sentences_;
};

#endif //HOMEWORK3_SRC_KNOWLEDGE_BASE_H
