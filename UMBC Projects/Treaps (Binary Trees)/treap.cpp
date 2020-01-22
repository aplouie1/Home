// CMSC 341 - Fall 2019 - Project 3 
// File: treap.cpp

using namespace std ;

#include "treap.h"

Treap::Treap() {
  _nptr = nullptr ;
}


Treap::Treap(const Treap& other) {
  //
  // Implement copy constructor
  //
  _nptr = nullptr ;
  copy(other._nptr);
}


Treap::~Treap() {
  //
  // Implement destructor
  //
  delete _nptr;
}


const Treap& Treap::operator=(const Treap& rhs) {
  //
  // Implement assignment operator
  //
  // Ensures an empty Treap before assigning the other Treap
  if (this != &rhs) {
    delete _nptr;
    _nptr = nullptr;
    copy(rhs._nptr);
  }

  return *this;
}


// Return -1 if the treap is empty; otherwise, return value in _height.
int Treap::height() const {
  return _nptr ? _nptr->_height : -1 ;
}


// Return the priority of the root node of a Treap.
// Note: numeric_limits<priority_t>::min() returns the minimum value
// of the priority type.  We will only use int priorities, so this is
// the minimum integer value.
priority_t Treap::priority() const {
  return _nptr ? _nptr->_pri : numeric_limits<priority_t>::min() ;
}


const data_t* Treap::find(const data_t& x) {
  //
  // Implement find function
  //
  const data_t* dataPointer;

  // Empty check
  if ( empty() ) {
    dataPointer = nullptr;
    return nullptr;
  }

  // Data found
  else if (_nptr->_data == x) {
    dataPointer = &_nptr->_data;
    return dataPointer;
  }

  // Traverses to the right node
  else if (_nptr->_data < x) { 
    dataPointer = _nptr->_right.find(x);
  } 
  
  // Traverses to the left node
  else if (_nptr->_data > x) {
    dataPointer = _nptr->_left.find(x);
  }

  return dataPointer;
}


// Inorder traversal.  Recommend you NOT change this!!!
void Treap::inorder() {
  if ( empty() ) return ;

  cout << "(" ;
  _nptr->_left.inorder() ;

  cout << _nptr->_data << ":" << priority() << ":" << height() ;

  _nptr->_right.inorder() ;
  cout << ")" ;

  return  ;
}


// Used for debugging and grading.  Interprets the characters in
// position[] as directions in the tree.  E.g., "RLR" means, "starting
// from root, go right, then left, then right."  If position[] is an
// empty string, then it just locates the value a the root.
// See project description for details.
bool Treap::locate (const char position[], data_t& x, priority_t& p, int& h, int offset) {
  if (_nptr == nullptr) return false ;

  if (position[offset] == '\0') {
    x = _nptr->_data ;
    p = _nptr->_pri ;
    h = _nptr->_height ;
    return true ;
  }

  if (position[offset] == 'L') {
    return _nptr->_left.locate(position, x, p, h, offset+1) ;
  }

  if (position[offset] == 'R') {
    return _nptr->_right.locate(position, x, p, h, offset+1) ;
  }

  cerr << "Bad position character!\n" ;
  exit(17) ;

  return false ; 
}


// Basic BST insertion.  Does not allow duplicate values.
//
// Complete this function to do Treap insertion.
//
void Treap::insert(const data_t& x, const priority_t& p) {
  // Empty check
  if ( empty() ) {
    _nptr = new TreapNode(x, p) ;
  }

  // Duplicate check 
  if ( _nptr->_data == x || _nptr->_pri == p) {
    return;
  }

  // Traverses to the right node
  if (_nptr->_data < x) { 
    _nptr->_right.insert(x, p) ;
  } 
  
  // Traverses to the left node
  else if (_nptr->_data > x) {
    _nptr->_left.insert(x, p) ;
  }

  // Left rotation (right-right case)
  if (_nptr->_right.priority() > priority()) {
    _nptr = rotateLeft(_nptr);
  }

  
  // Right rotation (left-left case)
  else if (_nptr->_left.priority() > priority()) {
    _nptr = rotateRight(_nptr);
  }
  
  // Updates height
  updateHeight(_nptr);
}


bool Treap::remove(const data_t& x) {
  //
  // Implement treap element removal
  //
  bool dataFound;
  
  // Node not found
  if (empty()) {
    return !empty();
  }
  
  // Traverse to the left 
  else if (_nptr->_data > x) {
    dataFound = _nptr->_left.remove(x);
  }

  // Traverse to the right
  else if (_nptr->_data < x) {
    dataFound = _nptr->_right.remove(x);
  }

  // Data found
  if (_nptr->_data == x) {

    // No children - deletion
    if ((_nptr->_left._nptr == nullptr) && (_nptr->_right._nptr == nullptr)) {
      delete _nptr;
      _nptr = nullptr;
      return empty();
    }

    // Both children are not nullptr
    else if ((_nptr->_left._nptr != nullptr) &&
	     (_nptr->_right._nptr != nullptr)) {
      
      // Rotate left and continue deletion in the found node
      if (_nptr->_left.priority() < _nptr->_right.priority() ) {
	      _nptr = rotateLeft(_nptr);
	      dataFound = _nptr->_left.remove(x);
      }
      
      // Rotate right and continue deletion in the found node
      else if (_nptr->_left.priority() > _nptr->_right.priority() ) {
      	_nptr = rotateRight(_nptr);
      	dataFound = _nptr->_right.remove(x);
      }
            
    }
    
    // Only the left child is a nullptr
    else if (_nptr->_left._nptr == nullptr) {
      _nptr = rotateLeft(_nptr);
      dataFound = _nptr->_left.remove(x);
    }

    // Only the right child is a nullptr
    else if (_nptr->_right._nptr == nullptr) {
      _nptr = rotateRight(_nptr);
      dataFound = _nptr->_right.remove(x);
    }

  }

  // Updates height along with traversal
  updateHeight(_nptr);

  return dataFound;
}


// Treap::dump() just calls TreapNode::dump()
void Treap::dump() {
  if ( !empty() ) _nptr->dump() ;
}


// Helper function for the copy constructor
void Treap::copy(TreapNode* node) {
  // Inserts the node's data/priority/height and copies the tree in preorder
  if (node) {
    insert(node->_data, node->_pri);
    copy(node->_left._nptr);
    copy(node->_right._nptr);
  }
}


// Helper function for left rotation
TreapNode* Treap::rotateLeft(TreapNode* node) {
    TreapNode* x = node->_right._nptr;
    TreapNode* b = x->_left._nptr;

    x->_left._nptr = node;
    node->_right._nptr = b;

    updateHeight(node);
    
    return x;
}


// Helper function for right rotation
TreapNode* Treap::rotateRight(TreapNode* node) {
    TreapNode* y = node->_left._nptr;
    TreapNode* b = y->_right._nptr;

    y->_right._nptr = node;
    node->_left._nptr = b;

    updateHeight(node);

    return y;
}


// Helper function for updating height 
// (from original insertion implementation)
void Treap::updateHeight(TreapNode* node) {
  int leftHeight = node->_left.height();
  int rightHeight = node->_right.height();
  node->_height = 1 + ( leftHeight > rightHeight ? leftHeight : rightHeight );
}
  

ostream& operator<< (ostream& os, const Treap& T) {
  os << T._nptr ; 
  return os ;
}


TreapNode::TreapNode() : _height(0) {
  // Empty constructor body
}


TreapNode::TreapNode(const data_t& x, const priority_t& p) 
  : _data(x), _pri(p), _height(0) { 
  // Empty constructor body
}


TreapNode::~TreapNode() {
  // Empty destructor
  // Retained for debugging
}


// Dump the contents of a node
void TreapNode::dump() {
  cout << "===== TreapNode::dump()\n" ;
  cout << "      this = " << this << endl ; 
  cout << "      left = " << _left << endl ; 
  cout << "      right= " << _right << endl ; 
  cout << "      data = " << _data << endl ;
  cout << "      height = " << _height << endl ;
  _left.dump() ;
  _right.dump() ;
}

