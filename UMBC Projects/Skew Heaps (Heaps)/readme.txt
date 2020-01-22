Date: 11/2019
Project 4: Skew Heaps


The objectives of this programming assignment are:

- Implement a skew heap, an advanced heap data structure.
- Gain additional experience constructing and using binary trees.
- Learn to use function pointers and tagged unions.


Seperate compilation is done for a SkewHeap (which is file "m") and a TypedHeap (which is file "mt").
Tests are used for different aspects of the project by replacing the driver file.
Expected output for each test is given by its respective text file.



Introduction:

A skew heap is a type of heap data structure that, like a standard max-heap, has efficient insert(), max(), and removeMax() operations, but also allows for efficient merging of heaps. Unlike a standard heap, it is not space-efficient to implement a skew heap in an array or vector &ldash; we will have to use a linked binary tree structure.

Your skew heap must satisfy the Max-heap Property, which you were introduced to in Project 3: for any node w in the tree, the priority of w must be greater than the priorities of its two children. This property guarantees that the element with highest priority is always in the root node of the tree, and so reading the highest priority element is just a matter of accessing the data in the root node.

The special feature of a skew heap is the merge operation which combines two skew heaps into a single, valid skew heap. Let p1 and p2 be positions in two skew heaps (e.g. pointers to nodes). Further, suppose the methods left() and right() return positions of the left and right children, and priority() returns the priority of a position. The merge operation is defined recursively:



Assignment:

Your assignment is to implement the SkewHeap class which implements a skew heap that can store both strings and integers using the tagged union construction. In addition, SkewHeap allows the user to determine how priorities are computed by passing a pointer to a prioritization function to the constructor. In addition, the user can change the prioritization function of an existing skew heap using a setter method, and the class will rebuild the heap using the new prioritization.

You must complete an additional class that uses SkewHeap, the TypedHeap class. The TypedHeap class maintains two skew heaps: an integer heap and a string heap. The user provides a vector of strings to insert, which are processed as follows:

If the string represents an integer (consists only of decimal digits), then convert it to an integer and insert it into the integer skew heap.
If the string does not represent an integer (contains non-digit characters), insert it into the string skew heap.
In addition, the user may request, through a combineHeaps() method, that the string and integer heaps be merged into a third “total” heap. Functions to change the priority function and to dump the skew heaps must also be implemented.



Additional Requirements:

Requirement: You must use the supplied SkewHeap.h and TypedHeap.h files. You may not modify any of the public method prototypes or private data, although you may add private functions to SkewHeap.h.

Requirement: The implementation file for the SkewHeap class must be named SkewHeap.cpp. The implementation file for the TypedHeap class must be named TypedHeap.cpp.

Requirement: If a user attempts to merge two skew heaps with different priority functions, a domain_error exception must be thrown.

Requirement: You must implement the skew heap merge operation as described in the Introduction.

Requirement: The insert() function must implement the merge-based insertion method described in Other Operations.

Requirement: The removeTop() function must implement the merge-based removal methods described in Other Operations.

Requirement: The dump() function must print the elements of the skew heap in decreasing priority order.

Requirement: The max-heap property must hold after any call to insert(), removeTop(), or skewHeapMerge().