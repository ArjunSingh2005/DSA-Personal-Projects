#pragma once
#include <string>

#include "Node.h"

class AVLTree{
  private:
    Node *root;
    void visualizeTree(const Node* subtree, int indent=0) const;
  public:

    AVLTree();

    // we dont need a destructor or rule of 3 bc we're not implementing a delete
    
    void insert(const std::string&); // insert function
    int balanceFactor(const Node*) const; // returns the balance factor
    void printBalanceFactors() const; // calls helper function

    // Helper functions
    Node* insert(Node*, const std::string&); // helper insert function
    Node* rotateRight(Node*); // rotates the tree right
    Node* rotateLeft(Node*);  // rotates the tree left
    static int computed_height(const Node*); // computes height of tree
    void printBalanceFactors(const Node* subtree) const; // helper function to print balance factors and nodes in order

    // Visualize Tree function
    void visualizeTree() const { visualizeTree(root); }
};
