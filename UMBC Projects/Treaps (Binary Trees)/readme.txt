Date: 10/2019
Project 3: Treaps


The objectives of this programming assignment are:

- Practice constructing and using binary search trees.
- Practice writing basic rebalancing routines (single rotations).



Compilation is done through the makefile on a Unix system.
Tests are used for different aspects of the project by replacing the driver file.
Expected output for each test is given by its respective text file.



Introduction:

A treap is a combination of a binary search tree (BST) and a heap. You should be very familiar with BSTs at this point in the semester, but you probably haven't encountered heaps yet. For this project, you only need two concepts from heaps:

- Each node of the tree, in addition to holding a data value, will also store an integer priority value. Priority values should be unique; that is, no two nodes should have the same priority.

- The tree must have the Max-Heap Property: for any node 
w in the tree, the priority of w must be greater than the priorities of its two children.



Assignment:

Your assignment is to implement the Treap class using single rotation method described in the Introduction to maintain the treap properties. You must use the provided treap.h and treap.cpp files. You may not modify the public function declarations or private data, but you may add private helper functions.

Although several test programs are provided, you are responsible for thoroughly testing your program. It is particularly important that your code run without segmentation faults, memory leaks, or memory errors. Memory leaks are considered as bad as segmentation fault since many segmentation faults are caused by poorly written destructors. A program with a poorly written destructor might avoid some segmentation faults but will leak memory horribly. Memory leaks will incur a penalty similar to that of a segmentation fault.



Additional Requirements:

Requirement: You must use the supplied treap.h and treap.cpp files. You may not modify any of the public method prototypes or private data, although you may add private functions.

Requirement: Your find(), insert() and remove() methods must all run in time proportional to the height of the treap.

Requirement: Your implementation must not permit duplicate data values. If an attempt is made to insert a duplicate value, insert() should leave the treap unchanged; it should not throw an exception or cause the program to crash.

Requirement: The treap properties must hold after any call to insert() or remove(). These commands must produce a valid treap.

Requirement: Your code must use single rotations as described in the Introduction to maintain the treap properties.

Requirement: Except for insert(), the provided function implementations should not be modified.