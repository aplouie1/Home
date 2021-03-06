// File: Driver.cpp
// 
// Tests in order: insert(), rebalance(), remove(), inserting duplicates,
//                 removing keys not in the tree, remove return value,
//                 find return value, copy constructor, destructor,
//                 assignment operator, locate()
//

#include <iostream>
#include <stdexcept>
using namespace std;

#include "CTree.h"


int main() {

  CTree T;
  int n;
  
  
  // Insertions
  T.insert(14);
  T.insert(7);
  T.insert(25);  
  T.insert(3);
  T.insert(32);
  T.insert(9);
  T.insert(18);

  
  // Inserting duplicates
  T.insert(3);
  T.insert(32);
  T.insert(9);
  T.insert(18);
  
  // More insertions
  T.insert(1);
  T.insert(44);
  T.insert(12);
  T.insert(15);
  T.insert(4);
  T.insert(29);
  T.insert(10);
  T.insert(21);

  
  // Output
  cout << "Current tree" << endl;
  T.inorder(); cout << endl;

  
  // Removals
  cout << endl << "removing ..." << endl;
  n = 14;
  cout << "removing " << n << endl;  T.remove(n); T.inorder(); cout << endl;
  n = 12;
  cout << "removing " << n << endl; T.remove(n); T.inorder(); cout << endl;
  n = 7;
  cout << "removing " << n << endl; T.remove(n); T.inorder(); cout << endl;
  n = 25;
  cout << "removing " << n << endl; T.remove(n); T.inorder(); cout << endl;
  n = 3;
  cout << "removing " << n << endl; T.remove(n); T.inorder(); cout << endl;
  n = 29;
  cout << "removing " << n << endl; T.remove(n); T.inorder(); cout << endl;
  n = 32;
  cout << "removing " << n << endl; T.remove(n); T.inorder(); cout << endl;
  n = 15;
  cout << "removing " << n << endl; T.remove(n); T.inorder(); cout << endl;


  // Removing items that do not exist
  cout << endl;
  n = 19;
  cout << "removing " << n << endl; T.remove(n); T.inorder(); cout << endl;
  n = 101;
  cout << "removing " << n << endl; T.remove(n); T.inorder(); cout << endl;
  n = -32;
  cout << "removing " << n << endl; T.remove(n); T.inorder(); cout << endl;
  cout << endl;


  // Checks return values of find()
  n = 44;
  cout << "Find " << n << endl;
  if (T.find(n)) {
    cout << "found = " << n << endl;
  }
  else {
    cout << "did not find = " << n << endl;
  }
  cout << endl;

  n = 4;
  cout << "Find " << n << endl;
  if (T.find(n)) {
    cout << "found = " << n << endl;
  }
  else {
    cout << "did not find = " << n << endl;
  }
  cout << endl;

  n = 30;
  cout << "Find " << n << endl;
  if (T.find(n)) {
    cout << "found = " << n << endl;
  }
  else {
    cout << "did not find = " << n << endl;
  }
  cout << endl;

  n = 18;
  cout << "Find " << n << endl;
  if (T.find(n)) {
    cout << "found = " << n << endl;
  }
  else {
    cout << "did not find = " << n << endl;
  }
  cout << endl;

  n = 301;
  cout << "Find " << n << endl;
  if (T.find(n)) {
    cout << "found = " << n << endl;
  }
  else {
    cout << "did not find = " << n << endl;
  }
  cout << endl;


  // Checks return values of remove()
  n = 21;
  cout << "Remove " << n << endl;
  if (T.remove(n)) {
    cout << n << " removed\n";
  }
  else {
    cout << n << " not found\n";
  }
  T.inorder(); cout << endl;

  n = 90;
  cout << "Remove " << n << endl;
  if (T.remove(n)) {
    cout << n << " removed\n";
  }
  else {
    cout << n << " not found\n";
  }
  T.inorder(); cout << endl;

  n = 40;
  cout << "Remove " << n << endl;
  if (T.remove(n)) {
    cout << n << " removed\n";
  }
  else {
    cout << n << " not found\n";
  }
  T.inorder(); cout << endl << endl;

  
  // Tests for copy constructor, destructor, and assignment operator
  cout << "Original:         ";
  T.inorder(); cout << endl;

  // Copy constructor
  CTree *Tptr = new CTree(T);

  cout << "Copied T1:           ";
  Tptr->inorder(); cout << endl;

  CTree T2;
  T2.insert(50);
  T2.insert(25); T2.insert(75);

  
  // Assignment operator
  T2 = *Tptr;
  cout << "Second copy:         ";
  T2.inorder(); cout << endl;

  
  // Destructor
  cout << "Delete first copy...\n";
  delete Tptr;

  cout << "Recheck original:    ";
  T.inorder(); cout << endl;
  cout << "Recheck second copy: ";
  T2.inorder(); cout << endl << endl;


  // Tests for locate()
  int key = 9999;
  bool ans;
  const char *str;

  ans = T.locate(str = "", key = -1);
  cout << str << ": " << ans << " " << key << endl;

  ans = T.locate(str = "LL", key = -1);
  cout << str << ": " << ans << " " << key << endl;

  ans = T.locate(str = "LLR", key = -1);
  cout << str << ": " << ans << " " << key << endl;

  ans = T.locate(str = "RLLR", key = -1);
  cout << str << ": " << ans << " " << key << endl;
  
}







