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
#include "literal.h"
#include "knowledge_base.h"

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
  Input(const std::string input_file_name) {
    ReadFromFile(input_file_name);
  }

  std::vector<Literal> get_queries() {
    return queries_;
  }

  KnowledgeBase get_knowledge_base() {
    return knowledge_base_;
  }

protected:
  void ReadFromFile(const std::string file_name);

  void ReadQueries(std::ifstream &input_stream);

  void ReadKnowledgeBase(std::ifstream &input_stream);

  std::string GetTrimmedLine(std::istream &input_stream) const {
    std::string read_line;
    std::getline(input_stream, read_line);
    // Trimming whitespace from the read line
    std::string::iterator new_end = std::remove(read_line.begin(),
                                                read_line.end(), ' ');
    read_line.erase(new_end - read_line.begin());
    return read_line;
  }

  std::vector<Literal> queries_;
  KnowledgeBase knowledge_base_;
};

#endif //HOMEWORK3_SRC_INPUT_H
