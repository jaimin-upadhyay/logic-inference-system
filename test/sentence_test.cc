//
// Created by Jaimin Upadhyay on 11/20/2016.
//

#include <gtest/gtest.h>
#include "sentence.h"

TEST(SentenceTest, ParseValidSentences) {
  std::vector<std::string> sentence_input_string = {
      "Student(Harry,Hogwarts)   ", "~Student(Harry,Hogwarts)",
      "Student(Harry,Hogwarts)&Flawless(h)",
      "Student(Harry,Hogwarts)|Flawless(h)",
      "Student(Harry,Hogwarts)=>Flawless(h)", "(Student(Harry,Hogwarts))",
      "Student(Harry,Hogwarts)=>~Flawless(h)",
      "Student(Harry,Hogwarts)&Flawless(h)=>Student(h,Hogwarts)",
      "~Student(Harry,Hogwarts) | Flawless(h)",
      "~(Student(Harry,Hogwarts) & Flawless(h)) | Student(h,Hogwarts)",
      "Student(Harry,Hogwarts,Magic)   ",
      "~Student(Harry,Hogwarts,Physics,Fall)",
      "Student(h,Hogwarts)&Female(h)&Name(h,Hermoine)",
      "Student(r,Hogwarts)&Name(r,Ron)=>~Flawless(r)&Male(r)&Wizard(r)",
      "AnimalLover(x)=>Animal(y)=>~Kills(x,y)",
      "~Parent(x,y) | ~Ancestor(y,z) | Ancestor(x,z)",
      "Programmer(x) & Emulator(y) & People(z) & Provide(x,z,y) => Criminal(x)",
      "(~Work(j) & AtHome(j)) | Fail(j, Exam)",
      "(~(Incollege(x) | (Teacher(x) & Student(x))))"};
  std::vector<std::string> expected_sentence_representation = {
      " Student(Harry,Hogwarts) ",
      " ~Student(Harry,Hogwarts) ",
      " ( Student(Harry,Hogwarts) & Flawless(h) ) ",
      " ( Student(Harry,Hogwarts) | Flawless(h) ) ",
      " ( ~Student(Harry,Hogwarts) | Flawless(h) ) ",
      " Student(Harry,Hogwarts) ",
      " ( ~Student(Harry,Hogwarts) | ~Flawless(h) ) ",
      " ( ( ~Student(Harry,Hogwarts) | ~Flawless(h) ) | Student(h,Hogwarts) ) ",
      " ( ~Student(Harry,Hogwarts) | Flawless(h) ) ",
      " ( ( ~Student(Harry,Hogwarts) | ~Flawless(h) ) | Student(h,Hogwarts) ) ",
      " Student(Harry,Hogwarts,Magic) ",
      " ~Student(Harry,Hogwarts,Physics,Fall) ",
      " ( Student(h,Hogwarts) & ( Female(h) & Name(h,Hermoine) ) ) ",
      " ( ( ( ~Student(r,Hogwarts) | ~Name(r,Ron) ) | ~Flawless(r) ) & ( ( ( ~Student(r,Hogwarts) | ~Name(r,Ron) ) | Male(r) ) & ( ( ~Student(r,Hogwarts) | ~Name(r,Ron) ) | Wizard(r) ) ) ) ",
      " ( ( AnimalLover(x) | ~Kills(x,y) ) & ( ~Animal(y) | ~Kills(x,y) ) ) ",
      " ( ~Parent(x,y) | ( ~Ancestor(y,z) | Ancestor(x,z) ) ) ",
      " ( ( ~Programmer(x) | ( ~Emulator(y) | ( ~People(z) | ~Provide(x,z,y) ) ) ) | Criminal(x) ) ",
      " ( ( ~Work(j) | Fail(j, Exam) ) & ( AtHome(j) | Fail(j, Exam) ) ) ",
      " ( ( ( ~Incollege(x) | ~Incollege(x) ) & ( ~Incollege(x) | ~Student(x) ) ) & ( ( ~Teacher(x) | ~Incollege(x) ) & ( ~Teacher(x) | ~Student(x) ) ) ) "};
  for (int i = 18; i < sentence_input_string.size(); i++) {
    std::ostringstream test_sentence_print;
    test_sentence_print << "Sentence " << i << ": ";
    test_sentence_print << sentence_input_string[i] << "\n";
    ASSERT_NO_THROW(Sentence test_sentence(sentence_input_string[i]))
                  << test_sentence_print.str();
    Sentence test_sentence(sentence_input_string[i]);
    EXPECT_EQ(expected_sentence_representation[i],
              test_sentence.to_string())
              << test_sentence_print.str();
  }
}

TEST(SentenceTest, ParseValidHomeworkSentences) {
  std::vector<std::string> sentence_input_string = {
      "Student(Harry,Hogwarts)   ", "(~Student(Harry,Hogwarts))",
      "(Student(Harry,Hogwarts)&Flawless(h))",
      "(Student(Harry,Hogwarts)|Flawless(h))",
      "(Student(Harry,Hogwarts)=>Flawless(h))",
      "(Student(Harry,Hogwarts))",
      "(Student(Harry,Hogwarts)=>(~Flawless(h)))",
      "((Student(Harry,Hogwarts)&Flawless(h))=>Student(h,Hogwarts))",
      "((~Student(Harry,Hogwarts)) | Flawless(h))",
      "((~(Student(Harry,Hogwarts) & Flawless(h))) | Student(h,Hogwarts))",
      "Student(Harry,Hogwarts,Magic)   ",
      "(~Student(Harry,Hogwarts,Physics,Fall))",
      "((Student(h,Hogwarts)&Female(h))&Name(h,Hermoine))",
      "((Student(r,Hogwarts)&Name(r,Ron))=>(((~Flawless(r))&Male(r))&Wizard(r)))",
      "(AnimalLover(x)=>(Animal(y)=>(~Kills(x,y))))",
      "(((~Parent(x,y)) | (~Ancestor(y,z))) | Ancestor(x,z))",
      "((((Programmer(x) & Emulator(y)) & People(z)) & Provide(x,z,y)) => Criminal(x))"};
  std::vector<std::string> expected_sentence_representation = {
      " Student(Harry,Hogwarts) ",
      " ~Student(Harry,Hogwarts) ",
      " ( Student(Harry,Hogwarts) & Flawless(h) ) ",
      " ( Student(Harry,Hogwarts) | Flawless(h) ) ",
      " ( ~Student(Harry,Hogwarts) | Flawless(h) ) ",
      " Student(Harry,Hogwarts) ",
      " ( ~Student(Harry,Hogwarts) | ~Flawless(h) ) ",
      " ( ( ~Student(Harry,Hogwarts) | ~Flawless(h) ) | Student(h,Hogwarts) ) ",
      " ( ~Student(Harry,Hogwarts) | Flawless(h) ) ",
      " ( ( ~Student(Harry,Hogwarts) | ~Flawless(h) ) | Student(h,Hogwarts) ) ",
      " Student(Harry,Hogwarts,Magic) ",
      " ~Student(Harry,Hogwarts,Physics,Fall) ",
      " ( ( Student(h,Hogwarts) & Female(h) ) & Name(h,Hermoine) ) ",
      " ( ( ( ( ~Student(r,Hogwarts) | ~Name(r,Ron) ) | ~Flawless(r) ) & ( ( ~Student(r,Hogwarts) | ~Name(r,Ron) ) | Male(r) ) ) & ( ( ~Student(r,Hogwarts) | ~Name(r,Ron) ) | Wizard(r) ) ) ",
      " ( ~AnimalLover(x) | ( ~Animal(y) | ~Kills(x,y) ) ) ",
      " ( ( ~Parent(x,y) | ~Ancestor(y,z) ) | Ancestor(x,z) ) ",
      " ( ( ( ( ~Programmer(x) | ~Emulator(y) ) | ~People(z) ) | ~Provide(x,z,y) ) | Criminal(x) ) "
  };
  for (int i = 0; i < sentence_input_string.size(); i++) {
    std::ostringstream test_sentence_print;
    test_sentence_print << "Sentence " << i << ": ";
    test_sentence_print << sentence_input_string[i]
                        << "\n";
    ASSERT_NO_THROW(Sentence test_sentence(sentence_input_string[i]))
                  << test_sentence_print.str();
    Sentence test_sentence(sentence_input_string[i]);
    EXPECT_EQ(expected_sentence_representation[i],
              test_sentence.to_string())
              << test_sentence_print.str();
  }
}

TEST(SentenceTest, ParseInvalidSentences) {
  std::vector<std::string> sentence_input_string = {"", "~",
                                                    "Student(Harry,Hogwarts)&",
                                                    "|Student(Harry,Hogwarts)",
                                                    "Student(Harry,Hogwarts)=Flawless(h)",
                                                    "(Student(Harry,Hogwarts)",
                                                    "Student(Harry,Hogwarts)&&Flawless(h)=>Student(h,Hogwarts)",
                                                    "~Student(Harry,Hogwarts) (|) Flawless(h)",
                                                    "~((Student(Harry,Hogwarts) &) Flawless(h)) | Student(h,Hogwarts)"};
  for (int i = 0; i < sentence_input_string.size(); i++) {
    EXPECT_THROW(Sentence test_sentence(sentence_input_string[i]),
                 std::invalid_argument)
              << "\nSentence " << i << ": " << sentence_input_string[i];
    try {
      Sentence new_sentence(sentence_input_string[i]);
      std::cout << "\nSentence Representation: " << new_sentence << "\n";
    } catch (std::invalid_argument invalid_sentence) {
      EXPECT_EQ("Invalid sentence: " + sentence_input_string[i],
                invalid_sentence.what());
    }
  }
}