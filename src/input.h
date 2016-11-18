//
// Created by Jaimin Upadhyay on 11/12/2016.
//
// Defines a class to handle input for the logic inference system
//

#ifndef HOMEWORK3_SRC_INPUT_H
#define HOMEWORK3_SRC_INPUT_H

#include <iostream>
#include <vector>
#include <fstream>
#include "query.h"

// Handles input for the logic inference system based on following specification:
// <NQ = NUMBER OF QUERIES>
// <QUERY 1>
// …
// <QUERY NQ>
// <NS = NUMBER OF GIVEN SENTENCES IN THE KNOWLEDGE BASE>
// <SENTENCE 1>
// …
// <SENTENCE NS>
class Input {

public:
  //Reads input from given file name
  void ReadFrom(const std::string input_file_name);

  //Accessor for queries
  std::vector<Query> get_queries() {
    return queries_;
  }

  //Accessor for knowledge base
  std::vector<std::string> get_knowledge_base() {
    return knowledge_base_;
  }

protected:
  //Reads the given Updates the given vector of queries  an input stream
  void
  ReadQueries(std::ifstream &input_stream);

  //Create a knowledge base from an input stream
  void ReadKnowledgeBase(std::ifstream &input_stream);

  std::vector<Query> queries_;
  std::vector<std::string> knowledge_base_;
};

#endif //HOMEWORK3_SRC_INPUT_H
