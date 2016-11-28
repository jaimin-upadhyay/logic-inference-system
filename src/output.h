//
// Created by Jaimin Upadhyay on 11/13/2016.
//
// Implements overloaded stream input function for ease of output
//

#ifndef HOMEWORK_3_SRC_OUTPUT_H
#define HOMEWORK_3_SRC_OUTPUT_H

#include <iostream>
#include <vector>
#include <iterator>

// Facilitate easy output of vectors by overloading "<<" operator.
// Implementation has to be in the header file otherwise it's references in
// source files, which include the header, are not recognized by the compiler.
// One workaround to keep the implementation in a .cc file is to declare it beforehand
// with types it is expected to be used with.
// For example, to use it with vectors with string elements declare following
// in the .cc file with the implementation:
//  template std::ostream& operator<< (std::ostream &output_stream, std::vector<string> const& generic_vector);
// @Jaimin: Chose to have it in header because pre-declaring element types
// is counter-intuitive to its purpose.
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
