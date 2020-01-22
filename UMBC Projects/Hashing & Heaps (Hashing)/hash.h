// CMSC 341 - Fall 2019 - Project 5
// hash.h

// Templated, hash table implementation.  Each buckets is a heap.  A
// bucket contains objects with the same key values stored as a
// max-heap based on priority.  Collisions are resolved by linear
// probing.

// To work with Heap and HashTable, the template class T must provide
// the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

#ifndef _HASH_H
#define _HASH_H

#include <string>
#include "heap.h"

using std::string;

// Hash function typedef.  The hash function must return an 'unsigned
// int' value.  Reduction mod N is the responsiblity of the caller,
// not the hash function.
typedef unsigned (*hash_fn)(string);

class Grader;

template <class T>
class HashTable {

  friend Grader;
  
 public:
  // Constructor.  Requires table size and hash function.
  HashTable(unsigned size, hash_fn hash);

  // Destructor, copy, and assignment
  ~HashTable();
  HashTable(const HashTable<T>& ht);
  const HashTable<T>& operator=(const HashTable<T>& ht);

  // In-line functions
  
  // Table size; set by constructor
  unsigned tableSize() const { return _N; }
  // Number of entries in the table
  unsigned numEntries() const { return _n; }
  // Load factor
  float lambda() const { return ((float) _n) / _N; }

  // Main hash table functions
  
  // insert returns 'true' if successful; 'false' otherwise
  bool insert(const T& object);
  // getNext retrieves **and removes** the highest priority order of
  // type indicated by key.  It returns 'true' if successful; 'false'
  // otherwise.
  bool getNext(string key, T& obj);

  // Dump the entire hash table
  void dump() const;
  
private:
  unsigned _N;       // hash table size
  unsigned _n;       // current number of entries
  hash_fn _hash;     // hash function
  Heap<T> *_table;   // array of heaps

  // ***********************************************
  // Private helper function declarations go here! *
  // ***********************************************
  
};

// *****************************************
// Templated function definitions go here! *
// *****************************************

// Constructor
template <class T>
HashTable<T>::HashTable(unsigned size, hash_fn hash) {
  _N = size;
  _n = size - size;
  _hash = hash;
  _table = new Heap<T>[_N];
}


// Destructor
template <class T>
HashTable<T>::~HashTable() {
  delete [] _table;
  _table = nullptr;
  _hash = nullptr;
}


// Copy constructor
template <class T>
HashTable<T>::HashTable(const HashTable<T>& ht) {
  _N = ht._N;
  _n = ht._n;
  _hash = ht._hash;
  _table = new Heap<T>[_N];

  // Copy each heap from the other hash table
  for (unsigned i = _N - _N; i < _N; i++) {
    _table[i] = ht._table[i];
  }
}


// Assignment operator
template <class T>
const HashTable<T>& HashTable<T>::operator=(const HashTable<T>& ht) {
  // Check for self-assignment
  if (this != &ht) {
    _N = ht._N;
    _n = ht._n;
    _hash = ht._hash;
    delete [] _table;
    _table = new Heap<T>[_N];

    // Copy each heap from the other hash table;
    // a helper function may be used but unnecessary for a trivial amount
    // of code only used twice
    for (unsigned i = _N - _N; i < _N; i++) {
      _table[i] = ht._table[i];
    }
  }

  return *this;
}


// Inserts an object into the hash table; returns true if the 
// object is sucessfully insert and false otherwise
template <class T>
bool HashTable<T>::insert(const T& object) {
  // Initializations
  unsigned hashKey = _hash(object.key()) % tableSize();
  unsigned originalHash = hashKey;

  // Attempt to insert the object
  do {
    
    // Insert into an empty hash table index
    if (_table[hashKey].empty()) {
      _table[hashKey].insert(object);
      return true;
    }   

    // Insert into a hash table index with the same key value
    else if (_table[hashKey].readTop().key() == object.key()) { 
      _table[hashKey].insert(object);
      return true;
    }

    // Preparation for linear probing
    hashKey++;

    // Loop back to the start of the hash table
    if (hashKey == tableSize())
      hashKey = tableSize() - tableSize();
    
  } while (hashKey != originalHash);

  // Object not inserted
  return false;
}


// Reads and removes the highest priority object with the give key
template <class T>
bool HashTable<T>::getNext(string key, T& obj) {
  // Initializations
  unsigned hashKey = _hash(key) % tableSize();
  unsigned originalHash = hashKey;

  // Attempt to find the object
  do {
    
    // Condition: there are no objects in the used hash table index
    if (_table[hashKey].empty()) 
      return false;
    
    // Found the object in the hash table index with the same key value
    if (_table[hashKey].readTop().key() == key) {            
      obj = _table[hashKey].readTop();
      _table[hashKey].removeTop();
      return true;      
    }

    // Preparation for linear probing
    hashKey++;

    // Loop back to the start of the hash table
    if (hashKey == tableSize())
      hashKey = tableSize() - tableSize();

  } while (hashKey != originalHash);

  // Object not found
  return false;  

}


// Dumps the contents of the hash table in array-index order
template <class T>
void HashTable<T>::dump() const{
  for (unsigned i = tableSize() - tableSize(); i < tableSize(); i++) {
    cout << "[" << i << "]:" << endl;
    _table[i].dump();
  }
}


#endif
