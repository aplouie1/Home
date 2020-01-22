// File: CTree.h
//
// CMSC 341 Spring 2019
//
// Header file for CTree class
//

#ifndef _CTREE_H_
#define _CTREE_H_

const int INITIAL = 0;                               // Zero initialization
const int INDEX = 1;                                 // For index boundaries
const int HALF = 2;                                  // For constructing BSTs

const int LIMIT = 2;                                 // Size-balance property
const int ABS_LIMIT = -2;                            // values

const bool EXIST = true;                             // Value for truth

const char LEFT = 'L';                               // Characters for
const char RIGHT = 'R';                              // locating nodes
const char END = '\0';                               //

// Node class for CTree
class CNode {
  
public:

  // CNode constructor; readies a node with
  // the given data
  CNode(int key);
  
  // CNode desutrctor
  ~CNode();
  
  // Allow private access for CTree objects
  friend class CTree;
  
private:
  CNode *m_parent;   // Parent of node
  CNode *m_left;     // Left child of node
  CNode *m_right;    // Right child of node    
  int m_data;        // Data value for the node
  int m_height;      // Height in the subtree
  int m_size;        // Number of nodes (including itself)
  
};


class CTree {
  
public:

  // CTree default constructor; readies a CTree object
  // for invoked member functions **ready m_root in here
  CTree();

  // CTree copy constructor
  CTree(const CTree& other);

  // CTree destructor
  ~CTree();

  // CTree overloaded assignment operator
  const CTree& operator=(const CTree& rhs);

  // Helper function for copying
  void copy(CNode *node);
  
  // Helper function for the destructor
  void deletion();
  
  // Adds an item to CTree
  void insert(int key);

  // Finds and removes an item with a given key value
  bool remove(int key);

  // Reports whether the given key is stored in the tree
  bool find(int key);

  // Checks for rebalancing
  void check();

  // Rebalances a subtree of CTree
  void rebalance();

  // Sorts a subtree's nodes
  void sorting();

  // Retrieves the current node for a sorted array
  void retrieve();
  
  // Constructs a subtree from a sorted array
  CNode *subtree(int start, int end);
  
  // Performs an inorder traversal of the CTree and
  // outputs in respective order: "key:height:size"
  // with parentheses for subtrees
  void inorder();

  // Returns whether there is a node in a position
  // of the CTree and stores the key
  bool locate(const char *position, int& key);


private:

  CNode *m_root;       // Root of tree
  CNode *m_currNode;   // Current node for traversal
  CNode *m_rebalNode;  // Node that needs to be rebalanced
  CNode **m_array;     // Array for sorting
  int m_cap;           // Capacity for sorting
  int m_count;         // Counter for sorting
  bool m_dupe;         // Pseudo-flag for duplicate data
  bool m_rebalance;    // Pseudo-flag for rebalancing
  bool m_removal;      // Pseudo-flag for removal
  bool m_removed;      // Pseudo-flag for removed node
  bool m_key;          // Value for finding a key

};



#endif
