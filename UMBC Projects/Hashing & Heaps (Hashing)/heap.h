// CMSC 341 - Fall 2019 - Project 5
// heap.h
// Templated, vector-based heap implementation

// To work with Heap, the template class T must provide the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) overloaded insertion operator
// To work with Heap *and* HashTable, it also needs:
//  (d) key function (string key())

#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>
#include <vector>
#include <exception>
#include <utility>   // swap

using std::vector;
using std::endl;
using std::cout;
using std::swap;
using std::range_error;

// To work with Heap and HashTable, class T must provide the
// following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

class Grader;

template <class T>
class Heap {

  friend Grader;
  
public:
  // Constructor
  Heap();

  // Inline functions: size, empty, used 
  unsigned size() const { return _heap.size() - 1 ; }
  bool empty() const { return _heap.size() <= 1 ; }
  bool used() const { return _used ; }

  // Main heap operations: insert, read, remove
  void insert(const T& object);
  T readTop() const;
  void removeTop();

  // Dump the entire heap
  void dump() const;

  // Root node always has index 1
  static const unsigned ROOT = 1;
  
private:
  vector<T> _heap;   // Vector-based heap
  bool _used;        // Has the heap ever been used?  Needed for
		     // linear probing.

  // *********************************************
  // Private helper function declarations go here!
  // *********************************************

};

// ***************************************
// Templated function definitions go here!
// ***************************************

// Initializes the empty heap
template <class T>
Heap<T>::Heap() {
  T initObject;
  _heap.push_back(initObject);
  _used = false;
}


// Inserts object into the heap and maintains max-heap property
template <class T>
void Heap<T>::insert(const T& object) {
  // Insert the first object into the max-heap while setting _used
  if (size() == (ROOT - ROOT)) {
    _heap.push_back(object);
    _used = true;
  }

  // Insert the object into the max-heap
  else {
    _heap.push_back(object);
    unsigned child = size();
    unsigned parent = ROOT + ROOT;

    // Loop until the object is correctly placed in the max-heap
    // Condition: the object has the highest priority
    while (child != ROOT) {

      // Additional condition: object has lower priority than its parent
      if (_heap[child].priority() <= _heap[child/parent].priority()) 
        return;
      
      // Bubble up
      // (taking O(log n) time as each swap is assumed to take constant time)
      else {
        swap(_heap[child], _heap[child/parent]);
        child = child/parent;
      }

    }

  }
}


// Returns the highest priority element in the heap, but does not
// remove it from the heap
template <class T>
T Heap<T>::readTop() const {
  // range_error for calls on an empty heap
  if (empty())
    throw range_error("Heap<T>::readTop():"
		      "attempt to call on an empty heap.");

  return _heap[ROOT];
}


// Removes the highest priority element from the heap;
// max-heap property must remain after removal
template <class T>
void Heap<T>::removeTop() {
  // range_error for calls on an empty heap
  if (empty())
    throw range_error("Heap<T>::removeTop():" 
		      "attempt to call on an empty heap.");

  // Removal for a heap with only one element
  if (size() == ROOT)
    _heap.pop_back();

  // Removal for a heap with more than one element
  else {
    // Initializations
    unsigned ancestor = ROOT;
    unsigned factor = ROOT + ROOT;
    unsigned left = ancestor * factor;
    unsigned right = left + ROOT;

    // Swaps the highest priority element and the last element for deletion
    swap(_heap[ROOT], _heap[size()]);
    _heap.pop_back();
    
    // Bubble down
    // (taking O(log n) time as each swap is assumed to take constant time)
    // Condition: an element does not exist beyond the heap's size
    while (left <= size()) {

      // Check if an element to the right exists and one of the element's 
      // children has higher priority
      if ( right <= size() &&
	   (_heap[ancestor].priority() <= _heap[left].priority() ||
	    _heap[ancestor].priority() <= _heap[right].priority()) ) {
	    
	// Swap with the left element
	if (_heap[left].priority() > _heap[right].priority()) {
	  swap(_heap[ancestor], _heap[left]);
	  ancestor = left;
	}

	// Swap with the right element
	else if (_heap[left].priority() < _heap[right].priority()) {
	  swap(_heap[ancestor], _heap[right]);
	  ancestor = right;
	}

      }

      // Compare the current element's priority to its left element
      else if (_heap[ancestor].priority() < _heap[left].priority()) {
	swap(_heap[ancestor], _heap[left]);
	ancestor = left;
      }

      // Max-heap property is not violated at the element's location
      else 
	return;
      
      // Re-initialize left and right values for the next iteration
      left = ancestor * factor;
      right = left + ROOT;

    }

  }
}


// Dumps contents of the heap array in index order;
// must overload the insertion operator (operator<<)
template <class T>
void Heap<T>::dump() const {
  for (unsigned i = ROOT; i <= size(); i++) {
    cout << _heap[i] << endl;
  }
}

#endif
