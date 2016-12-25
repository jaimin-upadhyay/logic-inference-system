//
// Created by Jaimin on 12/22/2016.
//

#include "knowledge_base.h"

// Handles input for the logic inference system based on following specification:
// <NQ = NUMBER OF QUERIES>
// <QUERY 1>
// …
// <QUERY NQ>
// <NS = NUMBER OF GIVEN SENTENCES IN THE KNOWLEDGE BASE>
// <SENTENCE 1>
// …
// <SENTENCE NS>
// Reads the queries and knowledge base from the input file based on the specified format.
// Throws an invalid_argument exception if opening of file fails.
std::tuple<KnowledgeBase, std::vector<Literal>>
KnowledgeBase::ReadFromFile(const std::string &file_name) {
  std::ifstream input_stream(file_name);
  if (!input_stream.is_open()) {
    throw std::invalid_argument("Input file couldn't be opened");
  } else {
    std::vector<Literal> queries = ReadQueries(input_stream);
    KnowledgeBase knowledge_base = ReadKnowledgeBase(input_stream);
    input_stream.close();
    return make_tuple(knowledge_base, queries);
  }
}

// Reads the given input stream for the number of queries to expect.
// Stores all the expected queries.
std::vector<Literal> KnowledgeBase::ReadQueries(std::ifstream &input_stream) {
  std::vector<Literal> queries;
  int no_of_queries = 0;
  input_stream >> no_of_queries;
  input_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::string read_line;
  for (int i = 0; i < no_of_queries; i++) {
    queries.push_back(Literal(GetTrimmedLine(input_stream)));
  }
  return queries;
}

// Reads the given input stream for number of sentences to expect.
// Stores all the expected sentences to the knowledge base.
KnowledgeBase KnowledgeBase::ReadKnowledgeBase(std::ifstream &input_stream) {
  KnowledgeBase knowledge_base;
  int no_of_sentences = 0;
  input_stream >> no_of_sentences;
  input_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  for (int i = 0; i < no_of_sentences; i++) {
    knowledge_base.ParseSentenceExpression(GetTrimmedLine(input_stream));
  }
  return knowledge_base;
}

std::string KnowledgeBase::GetTrimmedLine(std::istream &input_stream) {
  std::string read_line;
  std::getline(input_stream, read_line);
  // Trimming whitespace from the read line
  std::string::iterator new_end = std::remove(read_line.begin(),
                                              read_line.end(), ' ');
  read_line.erase(static_cast<unsigned long>(new_end - read_line.begin()));
  return read_line;
}

void KnowledgeBase::Query(const std::string &input_file_name,
                          const std::string &output_file_name) {
  KnowledgeBase knowledge_base;
  std::vector<Literal> queries;
  std::tie(knowledge_base, queries) = knowledge_base.ReadFromFile(
      input_file_name);
  std::ofstream output_stream(output_file_name);
  if (!output_stream.is_open()) {
    throw std::invalid_argument("Output file couldn't be opened");
  } else {
    for (Literal &query:queries) {
      output_stream
          << (knowledge_base.Ask(query) ? "TRUE"
                                        : "FALSE")
          << "\n";
    }
    output_stream.close();
  }
}

bool KnowledgeBase::CanResolve(const std::set<Literal> &literal_set) {
  std::set<Literal>::iterator literal_set_iterator;
  for (literal_set_iterator = literal_set.begin();
       literal_set_iterator != literal_set.end(); literal_set_iterator++) {
    Literal resolution_literal = *literal_set_iterator;
    resolution_literal.negate();
    KnowledgeBaseIndex::SentenceEntry *resolution_sentence_index_entry = index_.GetSentenceIndexes(
        resolution_literal);
    if (resolution_sentence_index_entry != nullptr) {
      const KnowledgeBaseIndex::SentenceEntry *front_entry = resolution_sentence_index_entry;
      do {
        std::set<Literal> resolution_literal_set = store_[resolution_sentence_index_entry->get_index()];
        resolution_literal_set.erase(
            resolution_sentence_index_entry->get_literal());
        LiteralSet new_literal_set = literal_set;
        new_literal_set.erase(*literal_set_iterator);
        if (Unify(new_literal_set, resolution_literal_set, resolution_literal,
                  resolution_sentence_index_entry->get_literal())) {
          new_literal_set.insert(resolution_literal_set.begin(),
                                 resolution_literal_set.end());
          if (resolved_sets_.find(new_literal_set) != resolved_sets_.end()) {
            return resolved_sets_[new_literal_set];
          } else {
            resolved_sets_[new_literal_set] = false;
            if (CanResolve(new_literal_set)) {
              resolved_sets_[new_literal_set] = true;
              return true;
            }
          }
        }
        resolution_sentence_index_entry = index_.GetSentenceIndexes(
            resolution_literal);
      } while (resolution_sentence_index_entry != nullptr &&
               resolution_sentence_index_entry != front_entry);
    }
  }
  resolved_sets_[literal_set] = literal_set.empty();
  return literal_set.empty();
}


bool KnowledgeBase::Unify(LiteralSet &focus_set_1,
                          LiteralSet &focus_set_2,
                          const Literal &required_literal,
                          const Literal &found_literal) const {
  Theta focus_set_1_theta, focus_set_2_theta;
  if (GetTheta(false, required_literal, found_literal, focus_set_1_theta) &&
      GetTheta(true, found_literal, required_literal, focus_set_2_theta)) {
    return Unify(focus_set_1, focus_set_1_theta) &&
           Unify(focus_set_2, focus_set_2_theta);
  }
  return false;
}

bool KnowledgeBase::Unify(LiteralSet &focus_set, Theta &theta) const {
  std::set<Literal> unified_focus_set;
  std::set<Literal>::iterator focus_set_iterator;
  for (focus_set_iterator = focus_set.begin();
       focus_set_iterator !=
       focus_set.end(); focus_set_iterator++) {
    Literal new_literal = *focus_set_iterator;
    std::set<Term> new_literal_arguments_set;
    for (std::vector<Term>::iterator it = new_literal.begin();
         it != new_literal.end(); it++) {
      std::map<Term, Term>::const_iterator theta_pair = theta.find(*it);
      if (theta_pair != theta.end()) {
        if (new_literal_arguments_set.find(theta_pair->second) ==
            new_literal_arguments_set.end()) {
          *it = theta_pair->second;
        } else {
          return false;
        }
      }
      new_literal_arguments_set.insert(*it);
    }
    unified_focus_set.insert(new_literal);
  }
  focus_set = unified_focus_set;
  return true;
}

bool
KnowledgeBase::GetTheta(bool change_to_match,
                        const Literal &focus_literal,
                        const Literal &match_literal,
                        std::map<Term, Term> &theta) const {
  std::vector<Term>::const_iterator required_iterator, found_iterator;
  if (focus_literal.get_name() == match_literal.get_name() &&
      focus_literal.size() == match_literal.size()) {
    for (required_iterator = focus_literal.begin(),
             found_iterator = match_literal.begin();
         required_iterator != focus_literal.end() &&
         found_iterator != match_literal.end();
         required_iterator++,
             found_iterator++) {
      if (*required_iterator != *found_iterator) {
        if (required_iterator->is_constant() &&
            found_iterator->is_constant()) {
          return false;
        } else if (!required_iterator->is_constant() &&
                   (found_iterator->is_constant() || change_to_match)) {
          std::pair<std::map<Term, Term>::iterator, bool> insertion_result;
          insertion_result = theta.insert(
              std::make_pair(*required_iterator, *found_iterator));
          if (!insertion_result.second &&
              insertion_result.first->second != *found_iterator) {
            return false;
          }
        }
      }
    }
    if (required_iterator == focus_literal.end() &&
        found_iterator == match_literal.end()) {
      return true;
    }
  }
  return false;
}



