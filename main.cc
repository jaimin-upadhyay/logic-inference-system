//============================================================================
// Name        : CSCI 561: Homework 3 (Logic Inference)
// Author      : Jaimin Upadhyay
// Version     : 0.0
// Description : Validating sentences using known logic sentences
//============================================================================

#include <iostream>
#include "input.h"
#include "output.h"

// Used to toggle debugging output to cout stream
const bool kDEBUG = true;

// Toggles the debugging output to cout stream based on the parameter value
void SetDebugMode(const bool debug) {
  if (debug) {
    std::cout.clear();
  } else {
    std::cout.setstate(std::ios_base::failbit);
  }
}

int main() {
  const std::string input_file_name = "input.txt";
  const std::string output_file_name = "output.txt";
  SetDebugMode(kDEBUG);
  Input input;
  input.ReadFrom(input_file_name);
  std::cout << "Queries: " << input.get_queries() << "\n";
  std::cout << "Knowledge Base:" << input.get_knowledge_base() << "\n";
  return 0;
}