//
// Created by Jaimin Upadhyay on 11/12/2016.
//

#ifndef HOMEWORK3_SRC_INPUT_H
#define HOMEWORK3_SRC_INPUT_H

#include <iostream>
#include <vector>
#include <fstream>

//Handles input for the logic inference system based on given project specifications
class Input {
    std::vector<std::string> queries;
    std::vector<std::string> knowledgeBase;

    //Create a vector of queries from an input stream
    void readQueries(std::ifstream &inputStream, std::vector<std::string> &queries);

    //Create a knowledge base from an input stream
    void readKnowledgeBase(std::ifstream &inputStream, std::vector<std::string> &knowledgeBase);

public:
    void readFrom(const std::string inputFileName);

    std::vector<std::string> getQueries() {
        return queries;
    }

    std::vector<std::string> getKnowledgeBase() {
        return knowledgeBase;
    }
};

#endif //HOMEWORK3_SRC_INPUT_H
