#include "Tree.h"
#include <iostream>
#include <string>

using namespace std;


// Note: I usually wouldn't use curr but the starter code had curr so I'm using it here


// returns the middle String
static const string& midStr( const string& s1, const string& s2, const string& s3 ) {
  if (( s1 < s2 && s1 > s3 ) ||( s1 < s3 && s1 > s2 ) ) 
    return s1;
  else if (( s2 < s1 && s2 > s3 ) ||( s2 < s3 && s2 > s1 ) ) 
    return s2;
  else 
    return s3;
}

// returns the smallest string
static const string& minStr( const string& s1, const string& s2, const string& s3 ) {
  if ( s1 < s2 && s1 < s3 ) 
    return s1;
  else if ( s2 < s1 && s2 < s3 ) 
    return s2;
  else
    return s3;
}

// returns the max string
static const string& maxStr( const string& s1, const string& s2, const string& s3 ) {
  if ( s1 > s2 && s1 > s3 ) 
    return s1;
  else if ( s2 > s1 && s2 > s3 ) 
    return s2;
  else
    return s3;
}

// constructor
Tree::Tree() {
  root = NULL;
}

// implement destructor
Tree::~Tree() {
  while (root != nullptr) {
      remove(root->small); // Continuously remove the smallest element
  }
}



bool Tree::noChildren( Node* node ) const {
  return (node->left==nullptr) && (node->middle == nullptr) && (node->right == nullptr);
  // returns true if the node we are passing in doesn't have any children
}

// insert function
void Tree::insert( const string& word ) {
  if (root == nullptr) {
    root = new Node( word );
  } else {
    insert( root, word );
  }
}


// insert helper function
void Tree::insert( Node* curr, const string& word ) {
    if (noChildren(curr)) { // if we've reached a leaf node
      if (curr->numData == 1) {  // if the leaf node has space, we can just call addData on it.
        addData(curr, word);
      } else { // if the leaf node is full, calculate the min, mid, and max

        string min = minStr(curr->small, curr->large, word);
        string mid = midStr(curr->small, curr->large, word);
        string max = maxStr(curr->small, curr->large, word);

        if (curr == root) { // if we are splitting up towards a root
          Node* newRoot = new Node(mid); // our new root is the value of mid
          Node* leftChild = new Node(min); // left child is the smallest of the 3 values
          Node* rightChild = new Node(max);  // right child is the largest of the 3 values

          root = newRoot; // assign root to our newRoot
          root->left = leftChild; // assign root's left to leftChild
          root->middle = rightChild; // asign root's right to rightChild
          leftChild->parent = root; // assign leftChild's parent back towards the root
          rightChild->parent = root; // assign rightChild's parnet back towards the root
        } else { // Splitting up towards a non-root node
          Node* parent = curr->parent; // assign a value to our parent value
          Node* leftChild = new Node(min); // assign leftChild to our min  
          Node* rightChild = new Node(max); // assing rightChild to our max

        if (parent->numData == 1) { // if the parent has space, insert middle into the parent
          if (mid < parent->small) { // if mid is less than parent's small
            parent->large = parent->small; // set large to the current small
            parent->small = mid; // set small to the node we are inserting up
            parent->right = parent->middle; // set parent's right to parent's old middle
            parent->middle = rightChild; // set parent's middle to rightChild because it must be less than middle but it will be bigger than 
            parent->left = leftChild; // set parent's left to leftChild
          } else { // if mid is greater than parent's small
            parent->large = mid; // set parent's large to the value we are pushing up
            parent->right = rightChild;  // set parent->right to rightChild
            parent->middle = leftChild; // set parent-> middle to leftChild because parent->left must be smaller based off the property
            // no need to do anything to parent->left because it will by default be the smallest thing
          }
            parent->numData = 2;
          } else { // parent is full. we will call minStr, midStr and maxStr on the parent.
              string newMin = minStr(parent->small, parent->large, mid);  // get the min value of the parent node
              string newMid = midStr(parent->small, parent->large, mid);  // get the mid value of the parent node
              string newMax = maxStr(parent->small, parent->large, mid);  // get the max value of the parent node

              Node* newLeft = new Node(newMin); // new left is parent's smallest value
              Node* newRight = new Node(newMax); // new right is parent's largest value

              if (parent == root) { // If splitting the root
                Node* newRoot = new Node(newMid); // create a node for our new root with the mid value
                newRoot->left = newLeft; // our new Root's left child is newLeft
                newRoot->middle = newRight; // our new Root's right child is newRight
                root = newRoot; // set root equal to our new root
                newLeft->parent = root; // set child's parent pointer to the root
                newRight->parent = root; // set child's parent pointer to the root
              } else { // Propagate the split upward
                insert(parent, newMid); // recursively call insert on parent with newMid
              }
          }
            leftChild->parent = parent; // at the end, connect the children's parent pointer back to parent
            rightChild->parent = parent;
          }
        }
    } else { // continue traversing to find the correct node
if (word < curr->small) {
            insert(curr->left, word);
        } else if (curr->numData == 1 or word < curr->large) {
            insert(curr->middle, word);
        } else {
            insert(curr->right, word);
        }
    }
}

// addData helper function
void Tree::addData(Node* addHere, const string& word) {
    if (addHere->numData == 1) { // Insert into a node with one key
        if (word < addHere->small) {
            addHere->large = addHere->small; // Shift small to large
            addHere->small = word;          // Place new key in small
        } else {
            addHere->large = word;          // Place new key in large
        }
        addHere->numData = 2;
    } else { // Insert into a full node (requires split handling)
        throw runtime_error("addData was called incorrectly");
    }
}

// PreOrder helper function
void Tree::preOrder(const Node* curr) const {
  if (curr == nullptr) {
    return; // Base case: empty subtree
  }

  // Visit the current node
  cout << curr->small;
  if (curr->numData == 2) {
    cout << ", " << curr->large; // Print large if present
  }
  cout << ", "; // Add a comma after the current node

  // Recur for left, middle, and right subtrees
  preOrder(curr->left);
  preOrder(curr->middle);
  preOrder(curr->right);
}

// Preorder Function, calls helper function
void Tree::preOrder() const {
  if (root == nullptr) {
    cout << endl;
    return; // Empty tree
  }
  preOrder(root);
  cout << endl; //add newline
}

// inOrder helper function
void Tree::inOrder(const Node* curr) const {
  if (curr == nullptr) {
    return; // Base case: empty subtree
  }

  // Traverse the left subtree
  inOrder(curr->left);

  // Visit the small key
  cout << curr->small << ", ";

  // Traverse the middle subtree
  inOrder(curr->middle);

  // Visit the large key (if exists)
  if (curr->numData == 2) {
    cout << curr->large << ", ";
  }

  // Traverse the right subtree
  inOrder(curr->right);
}

// inOrder function, calls helper
void Tree::inOrder() const {
  if (root == nullptr) {
    cout << endl;
    return; // Empty tree
  }
  inOrder(root);
  cout << endl; // add newline
}

// postOrder helper function
void Tree::postOrder(const Node* curr) const {
  if (curr == nullptr) {
    return; // Base case: empty subtree
  }

  // Recur for left, middle, and right subtrees
  postOrder(curr->left);
  postOrder(curr->middle);
  postOrder(curr->right);

  // Visit the current node
  cout << curr->small;
  if (curr->numData == 2) {
    cout << ",  " << curr->large; // Print large if present
  }
  cout << ","; // Add a comma after the current node
}

void Tree::postOrder() const {
  if (root == nullptr) {
    cout << endl;
    return; // Empty tree
  }
  postOrder(root);
  cout << endl; // add newline
}

// remove function
void Tree::remove(const string& word) {
    Node* node = search(word); // Find the node containing the word
    if (!node) return; // If the word is not found, do nothing

    // Case 1: If the node is not a leaf, replace the word with its in-order successor
    if (!noChildren(node)) {
        Node* succ = node->middle;
        while (succ->left) { // Find the leftmost child in the right subtree
            succ = succ->left;
        }
        // Replace the word to remove with the successor's value
        if (node->small == word) {
            node->small = succ->small;
        } else {
            node->large = succ->small;
        }
        node = succ; // Now remove the successor
    }

    // Case 2: Remove the word from the leaf node
    if (node->numData == 2) {
        // If the node has two keys, just remove the target key
        if (node->small == word) {
            node->small = node->large;
        }
        node->numData = 1;
    } else {
        // If the node has one key, mark it as empty and fix the tree
        if (node == root) {
            delete root; // If it's the root, delete it and make the tree empty
            root = nullptr;
        } else {
            node->numData = 0; // Mark the node as empty
            fix(node); // Fix the tree starting from this node
        }
    }
}


void Tree::fix(Node* emptyNode) {
  if (emptyNode == root){ // if our node is the root
    if (emptyNode->numData == 0){ // if our node is empty as well
      if (emptyNode->left){ // if emptyNode's left exists, move it up
        root = emptyNode->left;
        root->parent = nullptr;
      } else{
        root = nullptr; // Tree becomes empty
      }
      delete emptyNode;
    }
    return;
  }

  // assign 
  Node* parent  = emptyNode->parent;
  Node* leftSib = nullptr;
  Node* rightSib = nullptr;

  // Identify our sibilings
  if (parent->left == emptyNode){ // scenario where parent left is the node, rightsib will be parent's middle
    rightSib = parent->middle;
  } else if (parent->middle == emptyNode){ // scenario where parent middle is the node, leftsib will be the parent's left
    leftSib = parent->left;
    if (parent->numData == 2) { // if there are 2 keys in our parent, this means that rightSib exists and rightSib will be parent's right
      rightSib = parent->right;
    }
  } else{ // scenario where parent right is the node, left sib will simply by parent's middle
    leftSib = parent->middle;
  }

  // Scenario 1: Borrow from Left Sibling
  if (hasTwoChildSibling(leftSib)) { // if left sibiling exists and we have two keys in our node
      emptyNode->small = parent->small; // Bring parent key down
      parent->small = leftSib->large; // Update parent key
      leftSib->numData = 1; // Left sibling loses a key
      return;
  }

  // Scenario 2: Borrowing from Right Sibiling
  if (hasTwoChildSibling(rightSib)){ // if right sibiling exists and we have two keys in our node
    emptyNode->small = parent->small; // bring parent key down
    if (parent->middle == rightSib){ // if right sibiling is the middle key
      parent->small = rightSib->small; // update parent key
      rightSib->small = rightSib->large; // update rightsib's small
    } else{
      parent->large = rightSib->small; // update parent key (in this scenario we set parent large to rightSib small because we are taking from the right. so it must be bigger than parent's small)
      rightSib->small = rightSib->large; // update rightSib's small
    }
    rightSib->numData = 1; // right sibiling loses a key
    return;
  }

  // Scenario 3: Merging with Left Sibiling 
  if (leftSib){ // if leftSibiling exists
    leftSib->large = parent->small; // parent key moves down
    leftSib->numData = 2; // update number of nodes in leftSib

    if (parent->numData == 2){ // if there are 2 keys in the parent
      parent->small = parent->large; //shift large over to the left
      parent->middle = parent->right; // assign middle to right subtree
      parent->right = nullptr; // assign right subtree to nullptr. we've basically shifted it over
    } else { // one key in the parent
      parent->middle = nullptr; // parent's middle points to nothing now. parent is empty
      if (parent == root) { // if the parent was the root then, our leftsib gets moved up and becomes the new root
          delete root; // delete current root
          root = leftSib; // set root to left sib
          root->parent = nullptr; // set root's parent to nullptr
          return; // return
        }
      }
          delete emptyNode; // delete the node we just made to clean up memory
      }

  // Scenario 4: Merging with Right Sibiling
  else if (rightSib){ // if rightSibiling exists
    rightSib->large = rightSib->small; // shift right sib small and set it to right sib's large
    rightSib->small = parent->small; // right sib's small becomes parent's small
    rightSib->numData = 2; // right sib now has 2 keys

    if (parent->numData == 2){ // if there are 2 keys in the parent
      parent->small = parent->large; // shift large over to the left
      parent->numData = 1;
    } else if (parent == root){ // if the parent is the root and it's empty
      delete root; // delete current root
      root = rightSib; //make root rightSib
      root->parent = nullptr; // point root's parent to nullptr
      return; 
    } else{
      parent->middle = nullptr; 
    }
    delete emptyNode;
  }

  // Recursively fix parent if it becomes invalid
  if (parent->numData == 0) {
      fix(parent);
  }
}


bool Tree::hasTwoChildSibling(Node* sib) const {
  if (sib == nullptr) {
    return false; // No sibling exists
  }
  return sib->numData == 2; // Sibling has two keys
}


Node* Tree::search(const string& word) {
  return search(root, word); // call helper function
}

Node* Tree::search( Node* curr, const string& word ) {
  // reached a nullptr means we weren't able to find the word, so we just return nullptr
  if (curr == nullptr){
    return nullptr;
  }
  if (word == curr->small or (word == curr->large and curr->numData == 2)) return curr; // return key if it's found

  // traverse the list
  if (word < curr->small){ // if word is less than smallest node, go left
    return search(curr->left, word);
  } else if (curr->numData == 1 and word < curr->large){ // if word is less than biggest node, go to middle
    return search(curr->middle, word);
  } else{ // otherwise, we go right
    return search(curr->right, word);
  }
}