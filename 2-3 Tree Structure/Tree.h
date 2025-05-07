#pragma once

#include "Node.h"

using std::string;

class Tree {
private:
  Node* root;

public:
  Tree();

  // maintain rule of 3
  ~Tree();
  Tree(const Tree&) = delete;
  Tree& operator=(const Tree&) = delete;

  void insert( const string & ); // insert function, will call helper
  void preOrder() const; // preOrder function, will call helper
  void inOrder() const; // inOrder function, will call helper
  void postOrder() const; // postOrder function, will call helper
  void remove( const string & ); // remove function, will call helper
  Node* search( const string & ); // search function, will call helper

private:

  bool noChildren(Node* curr) const; // returns boolean of whether the node has children
  void insert(Node* curr, const string& word); // insert helper
  void addData(Node* addHere, const string& word); // helper function to sort node when inserting
  void preOrder(const Node* curr) const; // print via preOrder
  void inOrder(const Node* curr) const; // print via inOrder
  void postOrder(const Node* curr) const; // print via postOrder
  void fix(Node* emptyNode); // fix helper function to remove
  bool hasTwoChildSibling(Node* sibling) const; // helper function that returns a boolean based off if a Node has two child sibilings or not
  Node* search(Node* curr, const string& word); // search helper function
};