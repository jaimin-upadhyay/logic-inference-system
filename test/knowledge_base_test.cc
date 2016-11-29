//
// Created by Jaimin Upadhyay on 11/28/2016.
//
#include "knowledge_base.h"

#include "gtest/gtest.h"

TEST(KnowledgeBaseTest, IndexTest) {
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
      "Programmer(x) & Emulator(y) & People(z) & Provide(x,z,y) => Criminal(x)"};
  std::string expected_kb_string = "Sentences: [ Student(Harry,Hogwarts) ,  ( ~Student(Harry,Hogwarts) | ~Flawless(h) ) ,  ( ( ~Student(Harry,Hogwarts) | ~Flawless(h) ) | Student(h,Hogwarts) ) ,  ( ~Student(Harry,Hogwarts) | Flawless(h) ) ,  ( ( ~Student(Harry,Hogwarts) | ~Flawless(h) ) | Student(h,Hogwarts) ) ,  Name(h,Hermoine) ,  Female(h) ,  Student(h,Hogwarts) ,  ( ( ~Student(r,Hogwarts) | ~Name(r,Ron) ) | Wizard(r) ) ,  ( ( ~Student(r,Hogwarts) | ~Name(r,Ron) ) | Male(r) ) ,  ( ( ~Student(r,Hogwarts) | ~Name(r,Ron) ) | ~Flawless(r) ) ,  ( ~Animal(y) | ~Kills(x,y) ) ,  ( AnimalLover(x) | ~Kills(x,y) ) ,  ( ~Parent(x,y) | ( ~Ancestor(y,z) | Ancestor(x,z) ) ) ,  ( ( ~Programmer(x) | ( ~Emulator(y) | ( ~People(z) | ~Provide(x,z,y) ) ) ) | Criminal(x) ) ]\n"
      "Index {\n"
      "\tAncestor: ( - : [ y: [ z: [13] ] ] ) ( + : [ x: [ z: [13] ] ] )\n"
      "\tAnimal: ( - : [ y: [11] ] ) ( + :  )\n"
      "\tAnimalLover: ( - : null ) ( + : [ x: [12] ] )\n"
      "\tCriminal: ( - : null ) ( + : [ x: [14] ] )\n"
      "\tEmulator: ( - : [ y: [14] ] ) ( + :  )\n"
      "\tFemale: ( - : null ) ( + : [ h: [6] ] )\n"
      "\tFlawless: ( - : [ h: [1, 2, 4], r: [10] ] ) ( + : [ h: [3] ] )\n"
      "\tKills: ( - : [ x: [ y: [11, 12] ] ] ) ( + :  )\n"
      "\tMale: ( - : null ) ( + : [ r: [9] ] )\n"
      "\tName: ( - : [ r: [ Ron: [8, 9, 10] ] ] ) ( + : [ h: [ Hermoine: [5] ] ] )\n"
      "\tParent: ( - : [ x: [ y: [13] ] ] ) ( + :  )\n"
      "\tPeople: ( - : [ z: [14] ] ) ( + :  )\n"
      "\tProgrammer: ( - : [ x: [14] ] ) ( + :  )\n"
      "\tProvide: ( - : [ x: [ z: [ y: [14] ] ] ] ) ( + :  )\n"
      "\tStudent: ( - : [ Harry: [ Hogwarts: [1, 2, 3, 4] ], r: [ Hogwarts: [8, 9, 10] ] ] ) ( + : [ Harry: [ Hogwarts: [0] ], h: [ Hogwarts: [2, 4, 7] ] ] )\n"
      "\tWizard: ( - : null ) ( + : [ r: [8] ] )\n"
      " }\n";
  KnowledgeBase test_knowledge_base;
  for (int i = 0; i < test_sentence_expressions.size(); i++) {
    std::ostringstream test_sentence_print;
    test_sentence_print << "Sentence " << i << ": ";
    test_sentence_print << test_sentence_expressions[i] << "\n";
    ASSERT_NO_THROW(test_knowledge_base.ParseSentenceExpression(
        test_sentence_expressions[i]))
                  << test_sentence_print.str();
  }
  std::ostringstream kb_string_stream;
  kb_string_stream << test_knowledge_base;
  ASSERT_EQ(expected_kb_string, kb_string_stream.str())
                << "\nKnowledge Base:\n" << kb_string_stream.str();
}