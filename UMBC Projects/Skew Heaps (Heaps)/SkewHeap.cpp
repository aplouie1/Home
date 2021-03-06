// CMSC 341 - Fall 2019 - Project 4
// File: SkewHeap.cpp

#include "SkewHeap.h"

// Constructor.  Must specify priority function.
SkewHeap::SkewHeap(pri_fn pri) {
  m_heap = nullptr;
  setPriFn(pri);
}


// Destructor
SkewHeap::~SkewHeap() {
  destroy(m_heap);
}


// Copy constructor
SkewHeap::SkewHeap(const SkewHeap& rhs) {
  priority = rhs.getPriFn();
  m_heap = copy(rhs.front());
}


// Assignment operator
const SkewHeap& SkewHeap::operator=(const SkewHeap& rhs) {
  if ( this != &rhs ) {
    destroy(m_heap);
    priority = rhs.getPriFn();
    m_heap = copy(rhs.front());
  }
  return *this;    
}


// Priority function get
pri_fn SkewHeap::getPriFn() const {
  return priority;
}


// Priority function set
void SkewHeap::setPriFn (pri_fn pri) {
  priority = pri;

  if ( !empty() ) {
    // Initializations
    SkewHeap tempHeap(priority);
    Node* leftHeap;
    Node* rightHeap;      

    // Loop to rebuild the heap to ensure its max-priority property
    while ( !empty() ) {
      leftHeap = m_heap->left;
      rightHeap = m_heap->right;
      m_heap->left = nullptr;
      m_heap->right = nullptr;

      // Insert a node from the original heap to the temporary heap
      tempHeap.m_heap = merger(tempHeap.m_heap, m_heap);
      
      // Removal and merging
      m_heap = merger(leftHeap, rightHeap);
    }

    // Set the original heap from the temporary heap
    m_heap = tempHeap.m_heap;
    tempHeap.m_heap = nullptr;
    tempHeap.setPriFn(nullptr);
  }
  
}


// Return true if the skew heap is empty
bool SkewHeap::empty() const {
  return m_heap == nullptr;
}


// Overloaded insertion operators for string data
void SkewHeap::insert(string data) {
  Node* strNode = new Node(data);
  m_heap = merger(m_heap, strNode);
}


// Overloaded insertion operation for integer data
void SkewHeap::insert(int data) {
  Node* intNode = new Node(data);
  m_heap = merger(m_heap, intNode);
}


// Access highest priority element in the skew heap.
Node* SkewHeap::front() const {
  if ( empty() ) return nullptr;
  return m_heap;
}


// Remove the highest priority element from the skew heap.
void SkewHeap::removeTop() {
  // Initializations
  Node* leftHeap;
  Node* rightHeap;
  leftHeap = m_heap->left;
  rightHeap = m_heap->right;

  // Removal and merging
  delete m_heap;
  m_heap = merger(leftHeap, rightHeap);
}


// Merge two heaps.  Merged heap in *this; sh is empty afterwards.
void SkewHeap::skewHeapMerge(SkewHeap& sh) {
  // domain_error for skew heaps with different priority functions
  if ( getPriFn() != sh.getPriFn() ) {
    throw std::domain_error("SkewHeap::skewHeapMerge(): attempt "
			    "to merge two skew heaps with "
			    "different priority functions.");
  }

  // Merge heaps and empties sh
  m_heap = merger(m_heap, sh.front());
  sh.m_heap = nullptr;
}


// Print inorder traversal.
void SkewHeap::inorder() const {
  nodePrint(front());
}
  

// Dump the contents of the heap in decreasing priority order.
void SkewHeap::dump() const {
  // Initializations for formatting
  int colWidth = 10;
  int colWidthTwo = 30;

  // Make a deep copy
  SkewHeap copy(getPriFn());
  copy = *this;

  // Loop to print in decreasing priority order
  while ( !copy.empty() ) {
    cout << "Data is:" << setw(colWidth);

    // Print data in the node
    if ( copy.front()->tagged_union == ISSTRING ) {
      cout << copy.front()->data_string << setw(colWidthTwo);
    }
    else if ( copy.front()->tagged_union == ISINT ) {
      cout << copy.front()->data_int << setw(colWidthTwo);
    }

    // Print priority with formatting
    cout << "Priority is:" << setw(colWidth)
	 << getPriFn()(copy.front()) << endl;

    // Removal from the dump copy
    copy.removeTop();
  }
}


// Helper function for deletion
void SkewHeap::destroy(Node* node) {
  if ( node != nullptr ) {
    destroy(node->left);
    destroy(node->right);
    delete node;
    node = nullptr;
  }
}


// Helper function for the copy constructor
Node* SkewHeap::copy(Node* node) {
  // Inserts the node's data and copies the heap in preorder
  if (node) {
    Node* newNode;    
    // Identify data in node
    if ( node->tagged_union == ISSTRING ) {
      newNode = new Node(node->data_string);
    }
    else if ( node->tagged_union == ISINT ) {
      newNode = new Node(node->data_int);
    }
    
    newNode->left = copy(node->left);
    newNode->right = copy(node->right);
    return newNode;
  }
  
  return nullptr;
}


// Helper function for printing
void SkewHeap::nodePrint(Node* node) const{
  if (node == nullptr) return;
  
  // Inorder traversal to the left
  cout << "(" ;
  nodePrint(node->left);
  
  // Prints the specified data at a node
  if ( node->tagged_union == ISSTRING ) {
    cout << node->data_string;
  }
  else if ( node->tagged_union == ISINT ) {
    cout << node->data_int;
  }
  
  // Inorder traversal to the right
  nodePrint(node->right);
  cout << ")" ;
}


// Helper function for merging
Node* SkewHeap::merger(Node* leftHeap, Node* rightHeap) {
  // If either heap is empty, return the other
  if ( leftHeap == nullptr ) {
    leftHeap = rightHeap;
    return leftHeap;
  }
  if ( rightHeap == nullptr ) {
    return leftHeap;
  }

  // Ensure the left heap has higher priority root 
  // by swapping each heap's root pointer
  Node* temp;
  if ( getPriFn()(leftHeap) < getPriFn()(rightHeap) ) {
    temp = leftHeap;
    leftHeap = rightHeap;
    rightHeap = temp;
  }

  // Swap the left and right children of the left heap
  temp = leftHeap->left;
  leftHeap->left = leftHeap->right;
  leftHeap->right = temp;

  // Recursively merge the left heap with the right heap;
  // make the merged heap the new left child of the current left heap
  leftHeap->left = merger(leftHeap->left, rightHeap);
  return leftHeap;
}
