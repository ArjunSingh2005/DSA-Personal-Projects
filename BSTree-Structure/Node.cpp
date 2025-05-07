#include "Node.h"

#include <iostream>

using namespace std;

// overload operator
ostream& operator<< ( ostream &os, const Node &a ) {
  os << a.key << "(" << a.count << ")";
  return os;
}

// constructor
Node::Node()
    : count(0),left(nullptr),right(nullptr)
{
}

// constructor
Node::Node(const string& s)
    : key(s),count(1),left(nullptr),right(nullptr)
{
}

Node::~Node() {
  // delete is safe on a nullptr.  No need to check
  delete left;
  delete right;
}

// copy constructor
Node & Node::operator=(const Node &rhs) {
  if (&rhs != this) {
    key = rhs.key;
    count = rhs.count;
  }
  return *this;
}
