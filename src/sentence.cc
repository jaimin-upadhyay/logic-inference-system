//
// Created by Jaimin Upadhyay on 11/19/2016.
//

#include <iostream>
#include <vector>
#include "sentence.h"

// Parses an input string to create a valid Sentence object.
// Parsing is done using a parsing table created from the following grammar:
//    S →	BA
//    A →	=>BA | ε
//    B →	DC
//    C →	vDC | ε
//    D → FE
//    E → ^FE | ε
//    F →	~G | G
//    G →	(S) | x
// where x is a predicate, v is OR, ^ is AND, ~ is NOT and => is IMPLICATION.
// Website used for grammar transformation and table generation: http://smlweb.cpsc.ucalgary.ca/
Sentence Sentence::ParseSentence(const std::string &input_string) {
  std::invalid_argument invalid_sentence_exception("Invalid sentence: " + input_string);
  // Symbols are stored in indexes equal to their column's index in the parsing table
  // '$' is used as a symbol for input end and 'x' is used as a symbol for predicates
  std::vector<char> symbol_table = {'$', 'x', ')', '(', '~', '&', '|', '=', '>'};
  const char kStartNonTerminal = '0';
  const unsigned int kInputEndSymbolIndex = 0, kPredicateSymbolIndex = 1, kClosingParenthesisSymbolIndex = 2, kOpeningParenthesisSymbolIndex = 3, kNotSymbolIndex = 4, kAndSymbolIndex = 5, kOrSymbolIndex = 6, kImplicationFirstHalfSymbolIndex = 7, kImplicationSecondHalfSymbolIndex = 8;
  // Digits denote the non-terminal symbols, "." denote an erroneous states and empty strings denote Epsilon states.
  std::vector<std::vector<std::string>> parsing_table = {{".", "21", ".", "21",  "21", ".",   ".",   ".",    "."},
                                                         {"",  ".",  "",  ".",   ".",  ".",   ".",   "=>21", "."},
                                                         {".", "43", ".", "43",  "43", ".",   ".",   ".",    "."},
                                                         {"",  ".",  "",  ".",   ".",  ".",   "|43", "",     "."},
                                                         {".", "65", ".", "65",  "65", ".",   ".",   ".",    "."},
                                                         {"",  ".",  "",  ".",   ".",  "&65", "",    "",     "."},
                                                         {".", "7",  ".", "7",   "~7", ".",   ".",   ".",    "."},
                                                         {".", "x",  ".", "(0)", ".",  ".",   ".",   ".",    "."}};
  std::vector<char> parsing_stack;
  std::vector<Predicate> predicates;
  std::vector<char> operators;
  std::vector<Node *> temp_roots;
  parsing_stack.push_back(kStartNonTerminal);
  std::string::const_iterator input_string_iterator = input_string.begin();
  std::regex predicate_regex(Predicate::kRegex);
  std::smatch predicate_regex_match;
  while (!parsing_stack.empty()) {
    unsigned int column_index = 0, row_index = 0;
    if (input_string_iterator == input_string.end()) {
      column_index = kInputEndSymbolIndex;
    } else if (isupper(*input_string_iterator)) {
      // If next input character is a upper case letter then expect a predicate
      column_index = kPredicateSymbolIndex;
    } else if (isspace(*input_string_iterator)) {
      // Ignore spaces in the input
      input_string_iterator++;
      continue;
    } else {
      unsigned int symbol_index;
      for (symbol_index = 0; symbol_index < symbol_table.size(); symbol_index++) {
        if (*input_string_iterator == symbol_table[symbol_index]) {
          column_index = symbol_index;
          break;
        }
      }
      if (symbol_index >= symbol_table.size()) {
        std::string invalid_char_message = "Invalid character \'";
        invalid_char_message.push_back(*input_string_iterator);
        invalid_char_message += "\' found in sentence \'" + input_string + "\'.";
        throw std::invalid_argument(invalid_char_message);
      }
    }
    if (isdigit(parsing_stack.back())) {
      row_index = parsing_stack.back() - '0';
      parsing_stack.pop_back();
      if (parsing_table[row_index][column_index] == ".") {
        throw invalid_sentence_exception;
      } else {
        if (parsing_table[row_index][column_index].empty()) {
          bool negate = false;
          while (!operators.empty() && !predicates.empty()) {
            if (operators.back() == symbol_table[kNotSymbolIndex]) {
              negate = true;
              operators.pop_back();
            } else {
              PredicateNode *operator_rvalue = new PredicateNode(predicates.back(), negate);
              negate = false;
              predicates.pop_back();
              Node *operator_lvalue;
              if (predicates.empty()) {
                if (!temp_roots.empty()) {
                  operator_lvalue = temp_roots.back();
                  temp_roots.pop_back();
                } else {
                  throw invalid_sentence_exception;
                }
              } else {
                operator_lvalue = new PredicateNode(predicates.back());
                predicates.pop_back();
              }
              char new_operator = operators.back();
              operators.pop_back();
              if (new_operator == symbol_table[kImplicationSecondHalfSymbolIndex]) {
                new_operator = symbol_table[kOrSymbolIndex];
                operator_lvalue->negate();
              }
              Node *new_operator_node = new OperatorNode(new_operator, operator_lvalue, operator_rvalue);
              temp_roots.push_back(new_operator_node);
            }
          }
          while (!predicates.empty()) {
            if (temp_roots.empty()) {
              temp_roots.push_back(new PredicateNode(predicates.back(), negate));
              negate = false;
              predicates.pop_back();
            } else {
              throw invalid_sentence_exception;
            }
          }
          while (!operators.empty()) {
            if (!temp_roots.empty()) {
              if (operators.back() == symbol_table[kNotSymbolIndex]) {
                negate = true;
                operators.pop_back();
              } else {
                Node *operator_rvalue = temp_roots.back();
                temp_roots.pop_back();
                if (negate) {
                  operator_rvalue->negate();
                }
                negate = false;
                Node *operator_lvalue;
                if (!temp_roots.empty()) {
                  operator_lvalue = temp_roots.back();
                  temp_roots.pop_back();
                } else {
                  throw invalid_sentence_exception;
                }
                char new_operator = operators.back();
                operators.pop_back();
                if (new_operator == symbol_table[kImplicationSecondHalfSymbolIndex]) {
                  new_operator = symbol_table[kOrSymbolIndex];
                  operator_lvalue->negate();
                }
                Node *new_operator_node = new OperatorNode(new_operator, operator_lvalue, operator_rvalue);
                temp_roots.push_back(new_operator_node);
              }
            } else {
              throw invalid_sentence_exception;
            }
          }
          if (negate) {
            temp_roots.back()->negate();
            negate = false;
          }
        } else {
          for (int i = parsing_table[row_index][column_index].size() - 1; i > -1; i--) {
            parsing_stack.push_back(parsing_table[row_index][column_index][i]);
          }
        }
      }
    } else {
      if (parsing_stack.back() == *input_string_iterator) {
        parsing_stack.pop_back();
        if (*input_string_iterator != symbol_table[kImplicationFirstHalfSymbolIndex] &&
            *input_string_iterator != symbol_table[kOpeningParenthesisSymbolIndex] &&
            *input_string_iterator != symbol_table[kClosingParenthesisSymbolIndex]) {
          operators.push_back(*input_string_iterator);
        }
        input_string_iterator++;
      } else if (parsing_stack.back() == symbol_table[kPredicateSymbolIndex] &&
                 std::regex_search(input_string_iterator, input_string.end(), predicate_regex_match,
                                   predicate_regex) && predicate_regex_match.position(0) == 0) {
        // If a predicate is expected, check if it exists and occurs next in the input
        parsing_stack.pop_back();
        Predicate new_predicate(predicate_regex_match[0]);
        predicates.push_back(new_predicate);
        input_string_iterator += predicate_regex_match.length(0);
      } else {
        throw invalid_sentence_exception;
      }
    }
  }
  // Sentence is valid if the stack is empty and there is no input left.
  if (input_string_iterator != input_string.end()) {
    throw invalid_sentence_exception;
  }
  Sentence new_sentence = Sentence(temp_roots[0]);
  temp_roots.clear();
  return new_sentence;
}