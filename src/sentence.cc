//
// Created by Jaimin Upadhyay on 11/19/2016.
//

#include <set>
#include "sentence.h"

// Symbols are stored in indexes equal to their precedence.
// Even though parenthesis are stored with other operators, they are treated
// as special marker symbols to keep track of expression precedence.
const char Sentence::kSymbol[] = {'(', '=', '>', '|', '&', '~', ')'};
const unsigned int Sentence::kNumberOfSymbols = 7,
    Sentence::kOpeningParenthesisIndex = 0, Sentence::kImpliesFirstIndex = 1,
    Sentence::kImpliesSecondIndex = 2, Sentence::kOrIndex = 3,
    Sentence::kAndIndex = 4, Sentence::kNotIndex = 5,
    Sentence::kClosingParenthesisIndex = 6;

// Parses an input string to create a valid sentence parse tree and
// returns the root of the tree.
// Parsing is done using Edsger Dijkstra's Shunting Yard algorithm based on
// following references;
// Article describing recursive descent expression parsing methods:
//  http://www.engr.mun.ca/~theo/Misc/exp_parsing.htm#shunting_yard
// Article describing Shunting Yard algorithm:
//  http://www.oxfordmathcenter.com/drupal7/node/628
Node *Sentence::ParseSentence(const std::string &input_string) {
  std::invalid_argument invalid_sentence_exception("Invalid sentence: " +
                                                   input_string);

  std::map<char, int> symbol_precedence;
  for (int i = 0; i < kNumberOfSymbols; i++) {
    symbol_precedence[kSymbol[i]] = i;
  }

  std::regex predicate_regex(Predicate::kRegex);

  std::vector<Node *> operand_stack;
  std::vector<char> operator_stack;

  std::string::const_iterator input_string_iterator = input_string.begin();
  while (input_string_iterator != input_string.end()) {
    // Ignore spaces in the input
    if (isspace(*input_string_iterator)) {
      input_string_iterator++;
    } else {
      std::map<char, int>::iterator symbol_match = symbol_precedence.find(
          *input_string_iterator);
      if (symbol_match != symbol_precedence.end()) {
        if (*input_string_iterator == kSymbol[kClosingParenthesisIndex]) {
          while (!operator_stack.empty() && operator_stack.back() !=
                                            kSymbol[kOpeningParenthesisIndex]) {
            Sentence::ConsumeOperator(operator_stack, operand_stack,
                                      invalid_sentence_exception);
          }
          if (operator_stack.empty()) {
            throw invalid_sentence_exception;
          } else {
            operator_stack.pop_back();
            input_string_iterator++;
          }
        } else if (operator_stack.empty() ||
                   *input_string_iterator ==
                   kSymbol[kOpeningParenthesisIndex] ||
                   symbol_precedence[*input_string_iterator] >=
                   symbol_precedence[operator_stack.back()]) {
          operator_stack.push_back(*input_string_iterator);
          input_string_iterator++;
        } else {
          Sentence::ConsumeOperator(operator_stack, operand_stack,
                                    invalid_sentence_exception);
        }
      } else {
        // Search for first instance of a predicate and check if it starts
        // from current input pointer.
        std::smatch predicate_regex_match;
        if (std::regex_search(input_string_iterator, input_string.end(),
                              predicate_regex_match,
                              predicate_regex) &&
            predicate_regex_match.position(0) == 0) {
          Predicate new_predicate(predicate_regex_match[0]);
          operand_stack.push_back(new LiteralNode(new_predicate));
          input_string_iterator += predicate_regex_match.length(0);
        } else {
          std::string invalid_char_message = "Invalid \'";
          invalid_char_message.push_back(*input_string_iterator);
          invalid_char_message += "\' found in \'" + input_string + "\'.";
          throw std::invalid_argument(invalid_char_message);
        }
      }
    }
  }
  // Create a sentence object after consuming all the operators in operator
  // stack.
  while (!operator_stack.empty()) {
    ConsumeOperator(operator_stack, operand_stack, invalid_sentence_exception);
  }
  Node *parse_tree_root = nullptr;
  if (operand_stack.size() == 1) {
    parse_tree_root = operand_stack.back();
    operand_stack.pop_back();
  } else {
    throw invalid_sentence_exception;
  }
  return parse_tree_root;
}

template<typename T>
T Sentence::PopAndGet(std::vector<T> &stack,
                      std::invalid_argument fail_exception) {
  if (stack.empty()) {
    throw fail_exception;
  } else {
    T top = stack.back();
    stack.pop_back();
    return top;
  }
}

// Consumes the top operator from the given operator stack using the given
// operand stack. Throws specified fail exception when an error is encountered.
void Sentence::ConsumeOperator(std::vector<char> &operator_stack,
                               std::vector<Node *> &operand_stack,
                               std::invalid_argument fail_exception) {
  char new_operator = Sentence::PopAndGet(operator_stack,
                                          fail_exception);
  if (new_operator == kSymbol[kNotIndex]) {
    // Negate the top on operand stack.
    Node *operand = Sentence::PopAndGet(operand_stack,
                                        fail_exception);
    operand->negate();
    operand_stack.push_back(operand);
  } else if (new_operator == kSymbol[kImpliesSecondIndex]) {
    char next_operator = Sentence::PopAndGet(operator_stack,
                                             fail_exception);
    // Throwing an exception when implication second half is not preceded by implication first half.
    if (next_operator != kSymbol[kImpliesFirstIndex]) {
      throw fail_exception;
    } else {
      // Add implication to the sentence after converting it to disjunction using the following rule:
      //  P=>Q <=> ~P|Q
      new_operator = kSymbol[kOrIndex];
      Node *right_operand = Sentence::PopAndGet(operand_stack,
                                                fail_exception);
      Node *left_operand = Sentence::PopAndGet(operand_stack,
                                               fail_exception);
      left_operand->negate();
      operand_stack.push_back(
          new OperatorNode(new_operator, left_operand, right_operand));
    }
  } else if (new_operator == kSymbol[kOrIndex] ||
             new_operator == kSymbol[kAndIndex]) {
    Node *right_operand = Sentence::PopAndGet(operand_stack, fail_exception);
    Node *left_operand = Sentence::PopAndGet(operand_stack, fail_exception);
    operand_stack.push_back(
        new OperatorNode(new_operator, left_operand, right_operand));
  } else {
    throw fail_exception;
  }
}

// Extracts parts of a sentence connected by conjunction.
void Sentence::GetPartSentences(
    std::vector<std::set<Literal>> &part_sentences) const {
  Node *traverse_node = nullptr;
  std::vector<Node *> node_stack;
  node_stack.push_back(root_);
  while (!node_stack.empty()) {
    traverse_node = node_stack.back();
    node_stack.pop_back();
    if (traverse_node->get_data_string()[0] == kAnd) {
      node_stack.push_back(traverse_node->get_left());
      node_stack.push_back(traverse_node->get_right());
    } else {
      std::set<Literal> part_sentence_literals;
      GetLiterals(traverse_node, part_sentence_literals);
      part_sentences.push_back(part_sentence_literals);
    }
  }
}

// Extracts all the literals from a sentence.
void Sentence::GetLiterals(Node *traverse_root,
                           std::set<Literal> &literals) const {
  Node *traverse_node = nullptr;
  std::vector<Node *> node_stack;
  node_stack.push_back(traverse_root);
  while (!node_stack.empty()) {
    traverse_node = node_stack.back();
    node_stack.pop_back();
    try {
      if (traverse_node->get_data_string()[0] != kAnd) {
        node_stack.push_back(traverse_node->get_left());
        node_stack.push_back(traverse_node->get_right());
      }
    } catch (LeafNode::LeafException leaf_exception) {
      LiteralNode *literal_node = (LiteralNode *) traverse_node;
      literals.insert(*literal_node);
    }
  }
}