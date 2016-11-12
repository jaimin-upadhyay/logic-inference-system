//
// Created by Jaimin Upadhyay on 11/12/2016.
//

#include "input.h"

#include <limits>

void Input::readQueries(std::ifstream &inputStream, std::vector<std::string> &queries) {
    int noOfQueries = 0;
    inputStream >> noOfQueries;
    inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string tempString;
    for (int i = 0; i < noOfQueries; i++) {
        std::getline(inputStream, tempString);
        queries.push_back(tempString);
    }
}

void Input::readKnowledgeBase(std::ifstream &inputStream, std::vector<std::string> &knowledgeBase) {
    int noOfSentences = 0;
    inputStream >> noOfSentences;
    inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string tempString;
    for (int i = 0; i < noOfSentences; i++) {
        std::getline(inputStream, tempString);
        knowledgeBase.push_back(tempString);
    }
}

void Input::readFrom(const std::string inputFileName) {
    std::ifstream inputStream(inputFileName);
    if (!inputStream.is_open()) {
        std::cerr << "Opening of input file failed...\n";
        throw std::invalid_argument("Input file couldn't be opened");
    } else {
        readQueries(inputStream, queries);
        readKnowledgeBase(inputStream, knowledgeBase);
        inputStream.close();
    }
}
