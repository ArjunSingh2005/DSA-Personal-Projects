#include "Node.h"

// constructor, set everything to nullptr and numData to 1 if initalized with nothing.
Node::Node()
  : numData(1),
    parent(nullptr),
    left(nullptr),
    middle(nullptr),
    right(nullptr)
{
}

//------------------------------------------------------------------------

// constructor when passing in word, set word to small of Node.
Node::Node(const string& word )
  : small(word),
    numData(1),
    parent(nullptr),
    left(nullptr),
    middle(nullptr),
    right(nullptr)
{
}