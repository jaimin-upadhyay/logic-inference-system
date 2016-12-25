//============================================================================
// Name        : CSCI 561: Homework 3 (Logic Inference)
// Author      : Jaimin Upadhyay
// Version     : 0.0
// Description : Validating sentences using known logic sentences
//============================================================================

#include <iostream>
#include <knowledge_base.h>

int main() {
  const std::string input_file_name = "input.txt";
  const std::string output_file_name = "output.txt";
  try {
    KnowledgeBase::Query(input_file_name, output_file_name);
  } catch (std::invalid_argument e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}