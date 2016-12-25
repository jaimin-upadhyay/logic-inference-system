//
// Created by Jaimin Upadhyay on 11/28/2016.
//
#include "knowledge_base.h"

#include "gtest/gtest.h"

class KnowledgeBaseTest : public ::testing::Test {
protected:
  std::vector<std::string> test_sentence_expressions = {
      "Student(Harry,Hogwarts) ",
      "Student(Harry,Hogwarts)=>~Flawless(h)",
      "Student(Harry,Hogwarts)&Flawless(h)=>Student(h,Hogwarts)",
      "~Student(Harry,Hogwarts) | Flawless(h)",
      "~(Student(Harry,Hogwarts) & Flawless(h)) | Student(h,Hogwarts)",
      "Student(h,Hogwarts)&Female(h)&Name(h,Hermoine)",
      "Student(r,Hogwarts)&Name(r,Ron)=>~Flawless(r)&Male(r)&Wizard(r)",
      "AnimalLover(x)=>Animal(y)=>~Kills(x,y)",
      "~Parent(x,y) | ~Ancestor(y,z) | Ancestor(x,z)",
      "Programmer(x) & Emulator(y) & People(z) & Provide(x,z,y) => Criminal(x)",
      "(~Work(j) & AtHome(j)) | Fail(j, Exam)"};
};

TEST_F(KnowledgeBaseTest, CreationTest) {
  KnowledgeBase test_knowledge_base;
  std::string expected_kb_string = "{\n"
      "[( Student(Harry,Hogwarts) ), ( ~Flawless(h) ,  ~Student(Harry,Hogwarts) ), ( ~Flawless(h) ,  ~Student(Harry,Hogwarts) ,  Student(h,Hogwarts) ), ( Flawless(h) ,  ~Student(Harry,Hogwarts) ), ( ~Flawless(h) ,  ~Student(Harry,Hogwarts) ,  Student(h,Hogwarts) ), ( Name(h,Hermoine) ), ( Female(h) ), ( Student(h,Hogwarts) ), ( ~Name(r,Ron) ,  ~Student(r,Hogwarts) ,  Wizard(r) ), ( Male(r) ,  ~Name(r,Ron) ,  ~Student(r,Hogwarts) ), ( ~Flawless(r) ,  ~Name(r,Ron) ,  ~Student(r,Hogwarts) ), ( ~Animal(y) ,  ~Kills(x,y) ), ( AnimalLover(x) ,  ~Kills(x,y) ), ( Ancestor(x,z) ,  ~Ancestor(y,z) ,  ~Parent(x,y) ), ( Criminal(x) ,  ~Emulator(y) ,  ~People(z) ,  ~Programmer(x) ,  ~Provide(x,z,y) ), ( AtHome(j) ,  Fail(j, Exam) ), ( Fail(j, Exam) ,  ~Work(j) )]\n"
      "[\n"
      "\tAncestor: ( - : [ K: nullptr, v: [y : [ K: nullptr, v: [z : [13]] ]] ] ) ( + : [ K: nullptr, v: [x : [ K: nullptr, v: [z : [13]] ]] ] )\n"
      "\tAnimal: ( - : [ K: nullptr, v: [y : [11]] ] ) ( + :  )\n"
      "\tAnimalLover: ( - : null ) ( + : [ K: nullptr, v: [x : [12]] ] )\n"
      "\tAtHome: ( - : null ) ( + : [ K: nullptr, v: [j : [15]] ] )\n"
      "\tCriminal: ( - : null ) ( + : [ K: nullptr, v: [x : [14]] ] )\n"
      "\tEmulator: ( - : [ K: nullptr, v: [y : [14]] ] ) ( + :  )\n"
      "\tFail: ( - : null ) ( + : [ K: nullptr, v: [j : [ K: [  Exam: [15, 16] ], v: nullptr ]] ] )\n"
      "\tFemale: ( - : null ) ( + : [ K: nullptr, v: [h : [6]] ] )\n"
      "\tFlawless: ( - : [ K: nullptr, v: [h : [1, 2, 4], r : [10]] ] ) ( + : [ K: nullptr, v: [h : [3]] ] )\n"
      "\tKills: ( - : [ K: nullptr, v: [x : [ K: nullptr, v: [y : [11, 12]] ]] ] ) ( + :  )\n"
      "\tMale: ( - : null ) ( + : [ K: nullptr, v: [r : [9]] ] )\n"
      "\tName: ( - : [ K: nullptr, v: [r : [ K: [ Ron: [8, 9, 10] ], v: nullptr ]] ] ) ( + : [ K: nullptr, v: [h : [ K: [ Hermoine: [5] ], v: nullptr ]] ] )\n"
      "\tParent: ( - : [ K: nullptr, v: [x : [ K: nullptr, v: [y : [13]] ]] ] ) ( + :  )\n"
      "\tPeople: ( - : [ K: nullptr, v: [z : [14]] ] ) ( + :  )\n"
      "\tProgrammer: ( - : [ K: nullptr, v: [x : [14]] ] ) ( + :  )\n"
      "\tProvide: ( - : [ K: nullptr, v: [x : [ K: nullptr, v: [z : [ K: nullptr, v: [y : [14]] ]] ]] ] ) ( + :  )\n"
      "\tStudent: ( - : [ K: [ Harry: [ K: [ Hogwarts: [1, 2, 3, 4] ], v: nullptr ] ], v: [r : [ K: [ Hogwarts: [8, 9, 10] ], v: nullptr ]] ] ) ( + : [ K: [ Harry: [ K: [ Hogwarts: [0] ], v: nullptr ] ], v: [h : [ K: [ Hogwarts: [2, 4, 7] ], v: nullptr ]] ] )\n"
      "\tWizard: ( - : null ) ( + : [ K: nullptr, v: [r : [8]] ] )\n"
      "\tWork: ( - : [ K: nullptr, v: [j : [16]] ] ) ( + :  )\n"
      "]\n"
      "}\n";
  for (int i = 0; i < test_sentence_expressions.size(); i++) {
    std::ostringstream test_sentence_print;
    test_sentence_print << "Sentence " << i << ": ";
    test_sentence_print << test_sentence_expressions[i] << "\n";
    ASSERT_NO_THROW(test_knowledge_base.ParseSentenceExpression(
        test_sentence_expressions[i])) << test_sentence_print.str();
  }
  std::ostringstream kb_string_stream;
  kb_string_stream <<
                   test_knowledge_base;
  ASSERT_EQ(expected_kb_string, kb_string_stream.str())
                << "\nKnowledge Base:\n" << kb_string_stream.str();
}

TEST_F(KnowledgeBaseTest, QueryTest) {
  std::vector<std::string> test_queries = {"Student(Harry,Hogwarts)",
                                           "~Flawless(Hermoine)"};
  std::vector<bool> expected_results = {true, true};
  KnowledgeBase test_knowledge_base;
  for (int i = 0; i < test_sentence_expressions.size(); i++) {
    test_knowledge_base.ParseSentenceExpression(test_sentence_expressions[i]);
  }
  for (int i = 0; i < test_queries.size(); i++) {
    EXPECT_EQ(expected_results[i],
              test_knowledge_base.Ask(Literal(test_queries[i])))
              << "Query " << i << ": " << test_queries[i];
  }
}