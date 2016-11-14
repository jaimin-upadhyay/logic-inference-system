//
// Created by Jaimin Upadhyay on 11/13/2016.
//

#ifndef HOMEWORK_3_SRC_OUTPUT_H
#define HOMEWORK_3_SRC_OUTPUT_H

#include <iostream>
#include <vector>
#include <iterator>

// Facilitate easy output of vectors by overloading "<<" operator.
// Implementation has to be in the header file otherwise its references in
// source files including the header are not recognized by the compiler.
// One workaround to keep the implementation in cc file is to declare it beforehand
// with types it is expected to be used with. For example, to use it with
// vectors with string elements declare following in the .cpp file with the implementation:
// template std::ostream& operator<< (std::ostream &output_stream, std::vector<string> const& generic_vector);
// @Jaimin: Chose to have it in header because pre-declaring types it could be
// used with was counter-intuitive to its purpose.
template<class T>
std::ostream &
operator<<(std::ostream &output_stream, std::vector<T> const &generic_vector) {
  output_stream << "[";
  copy(generic_vector.begin(), generic_vector.end() - 1,
       std::ostream_iterator<T>(output_stream, ", "));
  output_stream << generic_vector.back() << "]";
  return output_stream;
}

#endif //HOMEWORK_3_SRC_OUTPUT_H
