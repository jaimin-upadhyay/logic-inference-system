//
// Created by Jaimin Upadhyay on 11/12/2016.
//

#include "input.h"

#include <limits>

// Reads the given input stream for the number of queries to expect
// then stores all the expected number of queries from the following lines in
// the input stream
void Input::ReadQueries(std::ifstream &input_stream,
                        std::vector<std::string> *queries) {
  int no_of_queries = 0;
  input_stream >> no_of_queries;
  // Ignore remaining characters in the line after the number of queries to
  // avoid confusion in following stream reads
  input_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::string temp_string;
  for (int i = 0; i < no_of_queries; i++) {
    std::getline(input_stream, temp_string);
    queries->push_back(temp_string);
  }
}

// Reads the given input stream for the number of sentences to expect
// then stores all the expected number of sentences from the following lines
// in the input stream to the knowledge base
void Input::ReadKnowledgeBase(std::ifstream &input_stream,
                              std::vector<std::string> *knowledge_base) {
  int no_of_sentences = 0;
  input_stream >> no_of_sentences;
  // Ignore remaining characters in the line after the value of number of
  // sentences to avoid confusion in following stream reads
  input_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::string temp_string;
  for (int i = 0; i < no_of_sentences; i++) {
    std::getline(input_stream, temp_string);
    knowledge_base->push_back(temp_string);
  }
}

// Opens a input file stream for the given input file name
// then reads the queries and knowledge base from the input file stream based
// on the specified format
// Throws an invalid_argument exception if opening of file fails
void Input::ReadFrom(const std::string input_file_name) {
  std::ifstream input_stream(input_file_name);
  if (!input_stream.is_open()) {
    std::cerr << "Opening of input file failed...\n";
    throw std::invalid_argument("Input file couldn't be opened");
  } else {
    ReadQueries(input_stream, &queries_);
    ReadKnowledgeBase(input_stream, &knowledge_base_);
    input_stream.close();
  }
}