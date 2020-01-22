Date: 4/2019
Project 3: Chestnut Trees


The objectives of this programming assignment are:

- Practice using recursion in programs, and
- Become familiar with the binary search tree data structure.



Compilation is done through the makefile on a Unix system.



Introduction:

With AVL trees and Red-Black Trees, we maintain a balance condition to guarantee that the tree has O(log n) height. Are there other balance conditions that we can use to efficiently maintain a balanced tree?

In in a Chestnut Tree (CTree), a node is imbalanced if the difference of the sizes of the left and right subtrees exceeds two. We call this the size-balance property (analagous to the height-balance property for AVL trees). Insertion and deletion proceed as for an unbalanced binary search tree until we notice that the balance condition is violated; then we must rebalance the subtree of the CTree rooted at this node.

There is one method that we can always use to rebalance a subtree of a CTree: convert the entire subtree into a sorted array and then convert the array back into a perfectly balanced BST. Rebuilding is easy because the array is sorted. We can find the middle element of the array in constant time and make it the root of the new subtree. Then, we recursively build the left subtree and the right subtree using, respectively, the portion of the array that has keys smaller than the root and the portion of the array that has keys larger than the root. The result is a binary search tree that is as balanced as possible. (See Project 3 Examples.) The rebalance procedure takes O(t) on a BST subtree with t elements, so it is relatively inefficient. However, we don't have to rebalance very often.

Note: It is possible for a CTree to be imbalanced at two nodes x and y where x is an ancestor of y. In this situation, rebalance at x since this will also rebalance the subtree rooted at y. If you rebalance at y first, the time spent rebalancing at y is completely wasted since all that work is undone when you rebalance at x. (See Project 3 Examples.)

Is this really the best we can do to rebalance a CTree? Is there any way that we can used trinode restructuring from AVL trees? Unfortunately, there is no simple relationship between height-balanced and size-balanced BSTs: you can construct examples of BSTs that are height-balanced but not size-balanced, and vice versa. Nonetheless, there are some circumstances in which a trinode restructuring can be used to rebalance a CTree. (See Project 3 Examples for one example.)



Assignment:
Since you will choose the design of the class definitions, no header files will be distributed with this project. Instead, the requirements are:

- The name of the class must be CTree.
- The header file must be named CTree.h (case sensitive).
- A client program that includes CTree.h should compile correctly without including any other header files.
- Your CTree class must have the member functions with the specified signatures indicated below.
- The implementation of your member functions and any supporting functions must be placed in a single file named CTree.cpp.
- No STL classes may be used in this programming project.

In order to implement CTree efficiently, your data structure must be able to determine the size and height of a subtree in constant time. You must have data members for the height and size of a subtree in the class representing the root of a subtree of a CTree. The height and size data members must be updated whenever the height or size of that subtree changes. The update must not affect the asymptotic running time of insert, delete and search. These must still run in time proportional to the height of the tree.

To keep things simple for this project, we will just store int values in CTree. Although, well-written code should allow you to easily change the type of data stored in the data structure.



Implementation Notes:

You may start with a binary search tree class from the textbook or one provided by your instructor. You may also design your own. Each option has advantages and disadvantages.

A primary objective of this programming assignment is to have you use recursion. So, one component of grading will evaluate how elegantly you employ recursion to implement this data structure.

Running time is one of the most important considerations in the implementation of a data structure. Programs that produce the desired output but exceed the required running times are considered wrong implementations and will receive substantial deductions during grading.

The height of a leaf node is zero. In this implementation, leaf nodes contain data but have no left or right children; this differs from the textbook in which leaf nodes do not store data.

There are many places where the height and size of a node needs to be updated including, for example, in the rebalance procedure.

When you insert a key that is already in the binary search tree, you are supposed to do nothing. This means you have to be careful about how you update the sizes of the subtrees, because when you insert a duplicate, the size does not change.

When should you check if the tree needs to be rebalanced? One time to consider is after you modify the CTree in the insert() and remove() procedures.

However, you want to do the rebalancing as high up the tree as possible. (See note above.) So consider checking for rebalancing before you insert or remove an item since you are already descending a branch of the tree.

Another temptation is to insert() or remove() the item during the rebalance() procedure. This is possible, but not elegant. Concentrate on elegant uses of recursion in this project.