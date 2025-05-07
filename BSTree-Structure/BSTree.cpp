#include "BSTree.h"

#include <iostream>

using namespace std;

// insert function
void BSTree::insert(const string& key) {
  // if root is the only node in the tree, we dynamically create a new node, set it to root and then node
  if (root == nullptr){
    root = new Node(key);
    return;
}

Node* curr = root; // curr allows us to traverse the tree, starting at root
while(true){
  if (key == curr->key){  // if the key already exists in the tree, we simply increment count and return
    curr->count+= 1; 
    return; 
  }
  // if the key is less than curr's key, we search to the left of the tree
  if (key < curr->key){
    if (curr->left == nullptr){ // we've hit a leaf
      curr->left = new Node(key); // we create a new node, set it to curr's left and return
      return;
    }
    else{
      curr = curr->left; // move down the tree to the left if we haven't yet hit a leaf
    }
      }
  else{
    if(curr->right == nullptr){ //we've hit a leaf
      curr->right = new Node(key); // we create a new node, set it to curr's right and return
      return;
    }
    else{
      curr = curr->right; // move down the tree to the right if we haven't yet hit a leaf
    }
  }
    }
  }

// Helper function for search
bool BSTree::SearchHelper(Node* subtree, const string& key) const{
  if (subtree == nullptr) return false; // return false if the key isn't in the tree 
  if (key == subtree->key) return true; // if we've found the key, return true
  if (key < subtree->key) return SearchHelper(subtree->left,key); // traversal to the left if key is less than our new tree's root's key
  return SearchHelper(subtree->right, key); // traversal to the right if key is less than our new tree's root's key
}
  
// Search function that is called by user. calls Helper function
bool BSTree::search(const string& key) const {
  return SearchHelper(root,key);
}

// Returns largest string in the tree
string BSTree::largest() const {
  if (root == nullptr) return ""; // if the tree is empty, we return ""
  Node* max = root; // set max to root, allows us to traverse the list
  while(max->right != nullptr){ // Largest value will be on the right most side of the tree so we keep traversing until our current Node's right point is nullpointer
    max = max->right; // move down the tree to the right
  }
  return max->key; // return max key 
}
// Returns smallest string in the tree
string BSTree::smallest() const {
  if (root == nullptr) return ""; // if the tree is empty, we return ""
  Node* min = root; // set m to root, allows us to traverse the list
  while(min->left != nullptr){ // Smallest value will be on the right most side of the tree so we keep traversing until our current Node's left point is nullpointer
    min = min->left;
  }
  return min->key;
}

// Helper Height function
int BSTree::height_of(Node* currNode, const string& key) const{
  if (currNode == nullptr) return -1; // key cannot be found in subtree
  if (currNode->key == key){ // once we've find where the key is, we need to find the height of that subtree
    if(currNode->left == nullptr and currNode->right == nullptr){
      return 0;
    }

    // set the heights of the tree to -1 automatically
    int left_height = -1;
    int right_height = -1;
    
    if (currNode->left != nullptr) {
      left_height = height_of(currNode->left, currNode->left->key);
      // create new subtrees to find the height of
    }
    if (currNode->right != nullptr) {
      right_height = height_of(currNode->right, currNode->right->key);
      // create new subtrees to find the height of
    }
    
    return 1 + std::max(left_height, right_height); // base case to return
  }
  // Recursively search for the target node in the left or right subtree
  if (key < currNode->key){
    return height_of(currNode->left, key); // Search in left subtree
  }
  else{
    return height_of(currNode->right, key); // Search in right subtree
  }
}

// height function that user calls
int BSTree::height(const string& key) const {
  return height_of(root, key); // call helper funciton
}

// remove function that user calls
void BSTree::remove(const string& key) {
  remove(nullptr, root, key); // call helper function
}

// remove helper function
void BSTree::remove(Node* parent, Node* tree, const string& key) {
  if (tree == nullptr) return; // if tree is empty return

  // Traverse the tree to locate the node to remove
  if (key < tree->key){
    remove(tree, tree->left, key);
    } else if (key > tree->key) {
        remove(tree, tree->right, key);
    } else{

    // Edge case where the node we are removing has a count greater than 1
    if (tree->count > 1){
      tree->count--;
      return;
    }
    
    // Removing a leef node. simply just delete the node
    if (tree->left == nullptr and tree->right == nullptr){
      if (parent == nullptr){
        delete tree;
        root = nullptr;
      } else if (parent->left == tree){
        parent->left = nullptr; // set previous pointers to nullptr
        delete tree;
      } else{
        parent->right = nullptr; // set previous pointers to nullptr
        delete tree;
      }
    }

  // Case with one node or two nodes
  else{
    if (tree->left != nullptr){ // if the node to remove has a left child
      Node* predecessorParent = tree; // Original node
      Node* predecessor = tree->left; // original node of left hand side tree
      while(predecessor->right != nullptr){ // go to right most value of left tree
        predecessorParent = predecessor;
        predecessor = predecessor->right;
      }
      tree->key = predecessor->key; // copy values over
      tree->count = predecessor->count;

      remove(predecessorParent, predecessor, predecessor->key); // recursively call remove. will delete when it becomes leaf
    }
    else{ // in all other cases
      Node* successorParent = tree; // Original Node
      Node* successor = tree->right; // Original Node of right hand side tree
      while(successor->left != nullptr){ // go to left most value of right tree
        successorParent = successor;
        successor = successor->left;
      }
      tree->key = successor->key; // copy valyes over
      tree->count = successor->count;

      remove(successorParent, successor, successor->key); // recursively call remove. will delete when it becomes leaf
    }
    }
  }
}

  // Prints in preOrder calls helper function
  void BSTree::preOrder() const {
    preOrder(root);
    std::cout << endl;
  }

  // Prints in postOrder calls helper function
  void BSTree::postOrder() const {
    postOrder(root);
    std::cout << endl;
  }

  // Prints in inOrder calls helper function
  void BSTree::inOrder() const {
    inOrder(root);
    std::cout << endl;
  }

// helper PreOrder print function
void BSTree::preOrder(Node* tree) const {
  if (tree == nullptr) return; // base case, if node is null
  // print key, do left, do right
  std::cout << tree->key << "(" << tree->count << "), ";
  preOrder(tree->left);
  preOrder(tree->right);
}

// helper postOrder print function
void BSTree::postOrder(Node* tree) const {
  if (tree == nullptr) return; // base case, if node is null
  postOrder(tree->left);
  postOrder(tree->right);

  std::cout << tree->key << "(" << tree->count << "), ";
  // do left, do right, print key
  
}

// helper inOrder print function
void BSTree::inOrder(Node* tree) const {
  // do left, print key, do right
 if (tree == nullptr) return; // base case, if node is null

  inOrder(tree->left);
  std::cout << tree->key << "(" << tree->count << "), ";
  inOrder(tree->right);
}


void BSTree::debug(Node* tree, int indent) const {
  // This is a pre-order traversal that shows the full state of the tree
  if (tree == nullptr) return;
  for(int i=0;i<4*indent;++i) cout << ' ';
  cout << tree << ' ' << *tree << endl;
  debug(tree->left,indent+1);
  for(int i=0;i<4*indent;++i) cout << ' ';
  cout << "-" << endl;
  debug(tree->right,indent+1);
}
