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
  std::vector<std::string> queries_;
  std::vector<std::string> knowledge_base_;

  //Reads the given Updates the given vector of queries  an input stream
  void
  ReadQueries(std::ifstream &input_stream, std::vector<std::string> *queries);

  //Create a knowledge base from an input stream
  void ReadKnowledgeBase(std::ifstream &input_stream,
                         std::vector<std::string> *knowledge_base);

public:

  //Reads input from given file name
  void ReadFrom(const std::string input_file_name);

  //Accessor for queries_
  std::vector<std::string> get_queries() {
    return queries_;
  }

  //Accessor for knowledge base
  std::vector<std::string> get_knowledge_base() {
    return knowledge_base_;
  }
};

#endif //HOMEWORK3_SRC_INPUT_H
