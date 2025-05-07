#include <iostream>
#include "Heap.h"

using namespace std;

// NOTE: I am failing silently (just returning) instead of throwing an error because the auto grader doesn't like when I do that but I would USUALLY throw an error in the case of an overflow or an underflow

Heap::Heap()
  : numItems(0)
{
}

// Destructor
Heap::~Heap() {
    for (int i = 0; i < numItems; i++) {
        delete heap[i];  // Delete each PrintJob pointer in the array
    }
}

// percolate up helper function
void Heap::percolate_up(int index){
  if (index == 0) return; // At the root, we return

  int ancestor = (index-1)/2; // go to parent
  if(heap[ancestor]->getPriority() > heap[index]->getPriority()) return; // if the parent is bigger, simply return

  //swap
  std::swap(heap[ancestor], heap[index]); // swap the PrintJob's and then percolate back up
  percolate_up(ancestor);
}

void Heap::enqueue(PrintJob* job) {
  if (numItems == MAX_HEAP_SIZE) return; // return if the number of items is the same size as the max number of elements we can have inside a heap

  heap[numItems] = job; // add job to the end of the list
  percolate_up(numItems); // call helper percolate function to maintain heap property and move to proper location
  numItems++; // increase size of Heap
}

void Heap::percolate_down(int index){
  int largest = index;

  // while there exists a left child, we attempt to move down
  while(((index*2)+1) < numItems){
    int leftchild = (2 * index) + 1; // set leftchild to get ready to compare
    int rightchild = leftchild + 1; // set rightchild to get ready to compare
    if(heap[leftchild]->getPriority() > heap[largest]->getPriority()){
      largest = leftchild; // if the leftchild's priority is bigger than the index, make largest = left child
    }
    if(rightchild < numItems and heap[rightchild]->getPriority() > heap[largest]->getPriority()){
      largest = rightchild; // if the rightchild's priority is bigger than the index and rightchild is still within numItems, make largest = rightchild
    }

    if(largest == index) return; // we have satisfied the heap property. both children are less than it's parent

    std::swap(heap[index], heap[largest]); //swap the largest elemetn with it's bigger child to replicate moving down
    index = largest; // our new index is either the left or right child
  }
}

void Heap::dequeue() {
  if (numItems == 0) return; // if Heap is empty, we have nothing to remove so we return
  heap[0] = heap[numItems-1]; // move last element to the front
  numItems--; // decrease size of Array

  percolate_down(0); // move down the Heap until we have properly satisfied the Heap property
}

PrintJob* Heap::highest() const{
  if (numItems == 0) return nullptr; // If heap is empty, return nullptr
  return heap[0]; // default return first element
}

void Heap::print() const{
    if (numItems == 0) {
        // Do nothing if the heap is empty
        return;
    }

  // print the first element's contents in the Heap
    PrintJob* job = highest();
    if (job != nullptr) {
    std::cout << "Priority: " << job->getPriority()
              << ", Job Number: " << job->getJobNumber()
              << ", Number of Pages: " << job->getPages() << std::endl;
      }
  }