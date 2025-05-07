#include "HashTable.h"
#include "WordEntry.h"

HashTable::HashTable (int s) {
  size = s; // Set the size of the hash table
  hashTable = new std::list<WordEntry>[size]; // Dynamically allocate an array of lists
}


int HashTable::computeHash(const string &s) const {
  unsigned int hash = 0;
  for (char c : s) {
      hash = (hash * 31 + c) % size; // 31 is a prime number
      // i used chatgpt for this hash function
  }
  return hash;
}


// destructor
HashTable::~HashTable() {
    delete[] hashTable;
}

void HashTable::put(const string &s, int score) {

  int index = computeHash(s);
  for (auto &entry : hashTable[index]) { 
      if (entry.getWord() == s) { // if word exists in hash table, create a new entry and push it on the list at the appropriate array index
          entry.addNewAppearance(score);
          return;
      }
  }
  // If the word doesn't exist, create a new WordEntry and add it to the list
  WordEntry newEntry(s, score);  // Create a new WordEntry object
  hashTable[index].push_back(newEntry); // Add the new entry to the list
}

double HashTable::getAverage(const string &s) const {
  int index = computeHash(s);
  for (const auto &entry : hashTable[index]) {
      if (entry.getWord() == s) { // once we find the word, call get average on the word. 
          return entry.getAverage();
      }
  }
  return 2.0; // Neutral sentiment if word not found

}
bool HashTable::contains(const string &s) const {

  
      int index = computeHash(s);
      for (const auto &entry : hashTable[index]) {
          if (entry.getWord() == s) { 
              return true; // true if word is in hash table
          }
      } // reached the end of the loop which means that word is not in hash table
      return false; // false if word is not in hash table
}