#pragma once
#include "PrintJob.h"


class Heap {
private:
  static const int MAX_HEAP_SIZE = 10;

  PrintJob* heap[MAX_HEAP_SIZE];      // Notice this is an array of PrintJob pointers
  int numItems;  // current number of items in heap
  void percolate_up(int index);
  void percolate_down(int index);

public:
  /* Initializes an empty heap.*/
  Heap();

  // preserve rule of 3
  ~Heap();
  Heap& operator=(const Heap& other) = delete;
  Heap(const Heap& other) = delete;

  /* Inserts a PrintJob to the heap without
  violating max-heap properties.*/
  void enqueue(PrintJob* job);

  /* Removes the node with highest priority from the heap. 
  Follow the algorithm on priority-queue slides. */
  void dequeue();

  /* Returns the node with highest priority.*/
  PrintJob* highest() const;

  /* Prints the PrintJob with highest priority in the following format:
     Priority: priority, Job Number: jobNum, Number of Pages: numPages
     (Add a new line at the end.) */
  void print() const;

private:
};
