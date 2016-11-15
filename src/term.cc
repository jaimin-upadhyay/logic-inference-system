//
// Created by Jaimin Upadhyay on 11/15/2016.
//

#include <algorithm>
#include <regex>
#include "term.h"

Term::Term(const std::string &name, const std::string &name_regex_string,
           const std::string &invalid_name_message)
    : invalid_name_message_(invalid_name_message) {
  Term::name_regex_ = std::regex(name_regex_string);
  Term::set_name(name);
}
