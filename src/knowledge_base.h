//
// Created by Jaimin Upadhyay on 11/19/2016.
//

#ifndef HOMEWORK3_SRC_KNOWLEDGE_BASE_H
#define HOMEWORK3_SRC_KNOWLEDGE_BASE_H

#include <iostream>
#include <vector>

#include "sentence.h"
#include "output.h"

class KnowledgeBase {
public:
  void AddSentence(std::string input_string) {
    Sentence new_sentence = Sentence::ParseSentence(input_string);
    return sentences_.push_back(new_sentence);
  }

  unsigned int size() {
    return sentences_.size();
  }

  Sentence operator[](int i) {
    return sentences_[i];
  }

  friend std::ostream &operator<<(std::ostream &os, const KnowledgeBase &base) {
    os << base.sentences_;
    return os;
  }

protected:
  std::vector<Sentence> sentences_;
};

#endif //HOMEWORK3_SRC_KNOWLEDGE_BASE_H
