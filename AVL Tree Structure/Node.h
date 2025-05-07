#pragma once

#include <string>


// struct for the node, i added height as a variable
struct Node {
  std::string data;
  int count;
  int height;
  Node* left;
  Node* right;
  Node(const std::string& data);
};
