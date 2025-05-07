#pragma once
#include <stdexcept> // For standard exceptions like overflow_error, runtime_error, underflow_error
#include <string> // For using the string class
using std::string; // Use std::string directly without needing the "std::" prefix


using std::overflow_error;
using std::runtime_error;
using std::underflow_error;

template<typename T> // Template class to allow stack to handle any data type T
class stack {
  // Maximum size of the stack is a constant (20)
  static constexpr unsigned MAXSIZE = 20;
  T array[MAXSIZE]; // Array to hold the stack elements
  unsigned size; // Variable to track the current size of the stack
public:
  // Constructor initializes the size of the stack to 0 (empty stack)
  stack() : size(0) {}

  // Push method to add an element to the top of the stack
  void push(const T& value) {
    // If the stack is full, throw an overflow error
    if (size == MAXSIZE) throw overflow_error("Called push on full stack.");
    array[size++] = value; // Add value to the array and increment the size
  }

  // Check if the stack is empty
  bool empty() const { 
    return size == 0; // Return true if size is 0, meaning the stack is empty
  }

  // Pop method to remove the top element from the stack
  void pop() {
    if (size == 0) throw std::out_of_range("Called pop on empty stack.");
    --size; // Decrement the size to remove the first element
  }

  // Pop two elements from the stack
  void pop_two() {
    // If there is only one element in the stack, throw an out_of_range exception
    if (size == 1) throw std::out_of_range("Called pop_two on a stack of size 1.");
    // If the stack is empty, throw an out_of_range exception
    if (size == 0) throw std::out_of_range("Called pop_two on empty stack.");
    size = size - 2; // Decrease the size by 2 to remove the first 2 elements
  }

    // Get the top element of the stack
  T& top() { 
    // If the stack is empty, throw an underflow error
    if (size == 0) throw std::underflow_error("Called top on empty stack.");
    return array[size-1]; // Return the first element
  }
    // Get the top element of the stack by const reference
  const T& top() const { 
    if (size == 0) throw std::underflow_error("Called top on empty stack.");
    return array[size-1]; // Return the first element
  }
};
