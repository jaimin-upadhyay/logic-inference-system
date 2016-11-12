//============================================================================
// Name        : CSCI 561: Homework 3 (Logic Inference)
// Author      : Jaimin Upadhyay
// Version     : 0.0
// Description : Validating sentences using known logic sentences
//============================================================================

#include <iostream>

#define IS_DEBUG true

void setDebugMode(const bool debug) {
    if (debug) {
        std::cout.clear();
    } else {
        std::cout.setstate(std::ios_base::failbit);
    }
}

int main() {
    const char *infn = "input.txt";
    const char *outfn = "output.txt";
    setDebugMode(IS_DEBUG);
    std::cout << "Hello World!\n";
    return 0;
}