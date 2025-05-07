#include "AVLTree.h"

#include <iostream>
using namespace std;

// constructor
AVLTree::AVLTree()
  : root(nullptr)
{
}

// insert function
void AVLTree::insert(const std::string& key){
   root = insert(root, key);
};

// insert helper function
Node* AVLTree::insert(Node* subtree, const std::string& key) {
    // we've reached a node
    if (!subtree){ 
        return new Node(key);
    }

    // traverse the tree
    if (key < subtree->data){
        subtree->left = insert(subtree->left, key);
    }
    else if (key > subtree->data){
        subtree->right = insert(subtree->right, key);
    }
    else{
        subtree->count++; // Duplicates are not allowed
        return subtree;
    }

    // Update height of the current node
    subtree->height = 1 + std::max(computed_height(subtree->left), computed_height(subtree->right));

    // Get the balance factor to check for imbalance
    int balance = balanceFactor(subtree);

    // Perform rotations if the node is unbalanced
    // Left Left Case
    if (balance > 1 && key < subtree->left->data)
        return rotateRight(subtree);

    // Right Right Case
    if (balance < -1 && key > subtree->right->data)
        return rotateLeft(subtree);

    // Left Right Case
    if (balance > 1 && key > subtree->left->data) {
        subtree->left = rotateLeft(subtree->left);
        return rotateRight(subtree);
    }

    // Right Left Case
    if (balance < -1 && key < subtree->right->data) {
        subtree->right = rotateRight(subtree->right);
        return rotateLeft(subtree);
    }

    return subtree;
}

// we call computed_height to get the balance factor of the tree by calling computed height on the left and right and then subtracting leftheight - rightheight
int AVLTree::balanceFactor(const Node* subtree) const{
    if (subtree == nullptr) 
        return 0; // A null node has a balance factor of 0

    // get height of left and right subtree
    int leftHeight = computed_height(subtree->left);
    int rightHeight = computed_height(subtree->right);

    return leftHeight - rightHeight;
}


// This is a helper function that traverses the tree to compute the height
int AVLTree::computed_height(const Node* subtree) {
  if (subtree == nullptr) return 0;
  return max(computed_height(subtree->left),computed_height(subtree->right))+1;
}


// We visualize a tree as text (there are some notes about doing this with VizGraph
// but it has never been worth the effort to get that part working)
void AVLTree::visualizeTree(const Node* subtree,int indent) const {
  // Indenting some spaces
  for(int i=0;i<indent;++i) { // traverse through
    cout << ' ';
  }

  if (subtree == nullptr) {
    cout << "-empty-" << endl;
  } else {
    cout << subtree->data << ' ' << '(' << (computed_height(subtree->left)-computed_height(subtree->right)) << ')' << endl;
    visualizeTree(subtree->left,indent+4);
    visualizeTree(subtree->right,indent+4);
  }
}


// Right rotation for balancing
// Helper function
Node* AVLTree::rotateRight(Node* old_root) {
    Node* new_root = old_root->left;
    Node* new_root_right = new_root->right;

    // Perform rotation
    new_root->right = old_root;
    old_root->left = new_root_right;

    // Update heights
    old_root->height = 1 + std::max(computed_height(old_root->left), computed_height(old_root->right));
    new_root->height = 1 + std::max(computed_height(new_root->left), computed_height(new_root->right));

    return new_root;
}

// Left rotation for balancing
Node* AVLTree::rotateLeft(Node* old_root) {
    Node* new_root = old_root->right;
    Node* new_root_left = new_root->left;

    // Perform rotation
    new_root->left = old_root;
    old_root->right = new_root_left;

    // Update heights
    old_root->height = 1 + std::max(computed_height(old_root->left), computed_height(old_root->right));
    new_root->height = 1 + std::max(computed_height(new_root->left), computed_height(new_root->right));

    return new_root;
}


void AVLTree::printBalanceFactors() const{
    printBalanceFactors(root); // call helper function
    cout << endl; // Move to the next line after printing
}

void AVLTree::printBalanceFactors(const Node* subtree) const {
    if (!subtree) return;

    // Traverse left subtree
    printBalanceFactors(subtree->left);

    // Print current node's data and balance factor
    cout << subtree->data << "(" << balanceFactor(subtree) << "), ";
  
    // Traverse right subtree
    printBalanceFactors(subtree->right);
}
