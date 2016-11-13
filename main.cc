//============================================================================
// Name        : CSCI 561: Homework 3 (Logic Inference)
// Author      : Jaimin Upadhyay
// Version     : 0.0
// Description : Validating sentences using known logic sentences
//============================================================================

#include <iostream>

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
    const char *input_file_name = "input.txt";
    const char *output_file_name = "output.txt";
    SetDebugMode(kDEBUG);
    std::cout << "Hello World!\n";
    return 0;
}