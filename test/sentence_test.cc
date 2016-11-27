//
// Created by Jaimin Upadhyay on 11/20/2016.
//

#include <gtest/gtest.h>
#include "sentence.h"

TEST(SentenceTest, ParseValidSentences) {
  std::vector<std::string> sentence_input_string = {"Student(Harry,Hogwarts)   ", "~Student(Harry,Hogwarts)",
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
                                                    "Programmer(x) & Emulator(y) & People(z) & Provide(x,z,y) => Criminal(x)"};
  std::vector<std::string> expected_sentence_representation = {" Student(Harry,Hogwarts) ",
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
                                                               " ( ( Female(h) & Name(h,Hermoine) ) & Student(h,Hogwarts) ) ",
                                                               " ( ( ~Student(r,Hogwarts) | ~Name(r,Ron) ) | ( ( ~Flawless(r) & Male(r) ) & Wizard(r) ) ) ",
                                                               " ( ~AnimalLover(x) | ( ~Animal(y) | ~Kills(x,y) ) ) ",
                                                               " ( ( ~Parent(x,y) | ~Ancestor(y,z) ) | Ancestor(x,z) ) ",
                                                               " ( ( ( ( ~Programmer(x) | ~Emulator(y) ) | ~People(z) ) | ~Provide(x,z,y) ) | Criminal(x) ) "
  };
  for (int i = 0; i < sentence_input_string.size(); i++) {
    std::ostringstream test_sentence_print;
    test_sentence_print << "Sentence " << i << ": " << sentence_input_string[i] << "\n";
    ASSERT_NO_THROW(Sentence::ParseSentence(sentence_input_string[i]))
                  << test_sentence_print.str();
    ASSERT_EQ(expected_sentence_representation[i], Sentence::ParseSentence(sentence_input_string[i]).to_string())
                  << test_sentence_print.str();
  }
}

TEST(SentenceTest, ParseValidHomeworkSentences) {
  std::vector<std::string> sentence_input_string = {"Student(Harry,Hogwarts)   ", "(~Student(Harry,Hogwarts))",
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
  std::vector<std::string> expected_sentence_representation = {" Student(Harry,Hogwarts) ",
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
                                                               " ( ( ~Student(r,Hogwarts) | ~Name(r,Ron) ) | ( ( ~Flawless(r) & Male(r) ) & Wizard(r) ) ) ",
                                                               " ( ~AnimalLover(x) | ( ~Animal(y) | ~Kills(x,y) ) ) ",
                                                               " ( ( ~Parent(x,y) | ~Ancestor(y,z) ) | Ancestor(x,z) ) ",
                                                               " ( ( ( ( ~Programmer(x) | ~Emulator(y) ) | ~People(z) ) | ~Provide(x,z,y) ) | Criminal(x) ) "
  };
  for (int i = 0; i < sentence_input_string.size(); i++) {
    std::ostringstream test_sentence_print;
    test_sentence_print << "Sentence " << i << ": " << sentence_input_string[i] << "\n";
    ASSERT_NO_THROW(Sentence::ParseSentence(sentence_input_string[i]))
                  << test_sentence_print.str();
    ASSERT_EQ(expected_sentence_representation[i], Sentence::ParseSentence(sentence_input_string[i]).to_string())
                  << test_sentence_print.str();
  }
}

TEST(SentenceTest, ParseInvalidSentences) {
  std::vector<std::string> sentences = {"", "~", "Student(Harry,Hogwarts)&", "|Student(Harry,Hogwarts)",
                                        "Student(Harry,Hogwarts)=Flawless(h)", "(Student(Harry,Hogwarts)",
                                        "Student(Harry,Hogwarts)&&Flawless(h)=>Student(h,Hogwarts)",
                                        "~Student(Harry,Hogwarts) (|) Flawless(h)",
                                        "~((Student(Harry,Hogwarts) &) Flawless(h)) | Student(h,Hogwarts)"};
  for (std::string sentence:sentences) {
    ASSERT_THROW(Sentence::ParseSentence(sentence), std::invalid_argument) << "\nSentence: " << sentence << '\n';
    try {
      Sentence::ParseSentence(sentence);
    } catch (std::invalid_argument invalid_sentence) {
      ASSERT_EQ("Invalid sentence: " + sentence, invalid_sentence.what());
    }
  }
}