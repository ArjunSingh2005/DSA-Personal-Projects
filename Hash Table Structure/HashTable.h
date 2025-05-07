#pragma once

#include <string>
#include <list>
#include <iostream>
#include "WordEntry.h"

using namespace std;

class HashTable {

private:
  list<WordEntry> *hashTable;
  int size;

public:
  HashTable(int size);

  // preserve rule of 3
  ~HashTable();

  // Deleted Copy Constructor
  HashTable(const HashTable&) = delete;

  // Deleted Copy Assignment Operator
  HashTable& operator=(const HashTable&) = delete;
  
  bool contains(const string& word) const;
  double getAverage(const string& word) const; // gets average
  void put(const string& word , int score); // puts into hash table

private:
  int computeHash(const string &) const;
};
