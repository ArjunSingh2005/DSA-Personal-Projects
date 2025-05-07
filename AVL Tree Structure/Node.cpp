#include "Node.h"

#include <string>
// node constructor
Node::Node(const std::string& data)
  :data(data), count(1), height(1), left(nullptr), right(nullptr)
{
}
