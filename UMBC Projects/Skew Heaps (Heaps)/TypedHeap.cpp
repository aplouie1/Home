// CMSC 341 - Fall 2019 - Project 4
// File: TypedHeap.cpp

#include "TypedHeap.h"

// Provide a vector of strings.  For each string, determine whether
// it represents an integer; if so, insert it into the integer skew
// heap.  Otherwise, insert it into the string skew heap.
void TypedHeap::insertToHeaps(vector<string> vec) {
  // Initializations
  vector<int> intVector;
  string tempStr;
  string dataStr = "";
  char whitespace = ' ';
  int strRange, strBeginPos, strEndPos;
  int dataNum, decimal = 1, total = 0;
  bool stringFound = false;

  // Loop the vector for each string
  for ( vector<string>::iterator it = vec.begin(); it != vec.end(); it++) {

    // Initialize a string's position in possible whitespace
    if (it->find_first_not_of(whitespace) != it->npos) {
      strBeginPos = it->find_first_not_of(whitespace);
      strEndPos = it->find_last_not_of(whitespace);      
      strRange = strEndPos - strBeginPos + 1;
    
      // Trim trailing and leading whitespace off
      tempStr = it->substr(strBeginPos, strRange);

      // Determine if the substring is a string or integer
      for ( string::iterator itStr = tempStr.begin();
	    itStr != tempStr.end(); itStr++) {

	// Set flag for a string
	if ( (*itStr < '0') || (*itStr > '9') ) {
	  stringFound = true;
	}
	// Insert the integer representation into an integer vecotr
	else {
	  dataNum = (int) *itStr - '0';
	  intVector.push_back(dataNum);
	}
      
      }
    }          

    // Loop through each character of a string
    for ( string::iterator itStr = it->begin(); itStr != it->end(); itStr++) {
      
      // Make a string
      if (stringFound) {
	dataStr += *itStr;
      }
      
    }

    // Insertion to relevant heap
    // Insert string data into string heap
    if (stringFound) {
      stringHeap.insert(dataStr);
    }
    // Insert integer data into integer heap
    else {      
      // Transforms data from an integer vector into an integer
      for ( vector<int>::reverse_iterator it = intVector.rbegin();
	    it != intVector.rend(); it++) {
	
	total += *it * decimal;
	decimal *= 10;
	
      }
      intHeap.insert(total);
    }
      
    // Reset values to parse the next string
    dataStr = "";
    decimal = 1;
    total = 0;
    intVector.clear();
    stringFound = false;
  }
}


// Merge the integer and string heaps; save in totalHeap.
void TypedHeap::combineHeaps() {
  // Assign the integer heap to totalHeap before merging
  totalHeap = intHeap;
  totalHeap.skewHeapMerge(stringHeap);
    
  // Empty the integer and string heaps
  intHeap = nullptr;
  stringHeap = nullptr;
}


// Print all three heaps (integer, string, total).
void TypedHeap::printHeaps() const {
  cout << "IntHeap Holds:" << endl;
  intHeap.dump();
  cout << "StringHeap Holds:" << endl;
  stringHeap.dump();
  cout << "TotalHeap Holds:" << endl;
  totalHeap.dump();
}


// Change the priority function.
void TypedHeap::changePriority(pri_fn pri) {
  intHeap.setPriFn(pri);
  stringHeap.setPriFn(pri);
  totalHeap.setPriFn(pri);
}
  
