//
// Created by Jaimin Upadhyay on 11/12/2016.
//

#include "input.h"

// Reads the queries and knowledge base from the input file based on the specified format.
// Throws an invalid_argument exception if opening of file fails.
void Input::ReadFromFile(const std::string file_name) {
  std::ifstream input_stream(file_name);
  if (!input_stream.is_open()) {
    throw std::invalid_argument("Input file couldn't be opened");
  } else {
    ReadQueries(input_stream);
    ReadKnowledgeBase(input_stream);
    input_stream.close();
  }
}

// Reads the given input stream for the number of queries to expect.
// Stores all the expected queries.
void Input::ReadQueries(std::ifstream &input_stream) {
  int no_of_queries = 0;
  input_stream >> no_of_queries;
  input_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::string read_line;
  for (int i = 0; i < no_of_queries; i++) {
    queries_.push_back(Literal(GetTrimmedLine(input_stream)));
  }
}

// Reads the given input stream for number of sentences to expect.
// Stores all the expected sentences to the knowledge base.
void Input::ReadKnowledgeBase(std::ifstream &input_stream) {
  int no_of_sentences = 0;
  input_stream >> no_of_sentences;
  input_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  for (int i = 0; i < no_of_sentences; i++) {
    knowledge_base_.ParseSentenceExpression(GetTrimmedLine(input_stream));
  }
}
