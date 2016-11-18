//
// Created by Jaimin Upadhyay on 11/15/2016.
//

#include "term.h"

// Regex used to validate the constant
const char Constant::kRegex[] = "[A-Z][a-zA-Z]*";

// Regex used to validate the variable
const char Variable::kRegex[] = "[a-z]";