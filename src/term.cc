//
// Created by Jaimin Upadhyay on 11/15/2016.
//

#include "term.h"

// Regex used to validate the constant
const char Term::kConstantRegex[] = "\\s*[A-Z][a-zA-Z]*\\s*";

const char Term::kConstantErrorMessage[] = "Constant term should be a case-sensitive, alphabetical and beginning with a upper case letter";

// Regex used to validate the variable
const char Term::kVariableRegex[] = "\\s*[a-z]\\s*";

const char Term::kVariableErrorMessage[] = "Variables should be a single lower case letter";
