//
// Created by Jaimin Upadhyay on 11/29/2016.
//

#ifndef HOMEWORK3_SRC_MULTI_NODE_H
#define HOMEWORK3_SRC_MULTI_NODE_H

#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>


// Base class for nodes with multiple values.
class MultiNode {
public:
  virtual ~MultiNode() {};

  virtual std::string to_string() const =0;

  friend std::ostream &
  operator<<(std::ostream &os, const MultiNode &node) {
    os << node.to_string();
    return os;
  }
};

// Node using a hash map to store multiple values.
template<typename K, typename V>
class MapMultiNode : public std::map<K, V *>, public MultiNode {
public:
  virtual ~MapMultiNode() {
    typename MapMultiNode::iterator map_iterator = MapMultiNode::begin();
    while (map_iterator != MapMultiNode::end()) {
      if (map_iterator->second != nullptr) {
        delete map_iterator->second;
        map_iterator->second = nullptr;
      }
      map_iterator++;
    }
  }

  std::string to_string() const override {
    std::ostringstream node_string_stream;
    typename MapMultiNode::const_iterator map_iterator = MapMultiNode::begin();
    node_string_stream << "[ ";
    node_string_stream << map_iterator->first << ": ";
    if (map_iterator->second != nullptr) {
      node_string_stream << *(map_iterator->second);
    } else {
      node_string_stream << "nullptr";
    }
    for (map_iterator++;
         map_iterator != MapMultiNode::end(); map_iterator++) {
      node_string_stream << ", " << map_iterator->first << ": ";
      if (map_iterator->second != nullptr) {
        node_string_stream << *(map_iterator->second);
      } else {
        node_string_stream << "nullptr";
      }
    }
    node_string_stream << " ]";
    return node_string_stream.str();
  }

  friend std::ostream &
  operator<<(std::ostream &os, const MapMultiNode<K, V> &node) {
    os << node.to_string();
    return os;
  }
};

// Node which uses a vector to store multiple values.
template<typename T>
class VectorMultiNode : public std::vector<T>, public MultiNode {
public:
  std::string to_string() const override {
    std::ostringstream node_string_stream;
    node_string_stream << "[";
    copy(VectorMultiNode::begin(), VectorMultiNode::end() - 1,
         std::ostream_iterator<T>(node_string_stream, ", "));
    node_string_stream << VectorMultiNode::back() << "]";
    return node_string_stream.str();
  }

  friend std::ostream &
  operator<<(std::ostream &output_stream, const VectorMultiNode &node) {
    output_stream << node.to_string();
    return output_stream;
  }
};

#endif //HOMEWORK3_SRC_MULTI_NODE_H
