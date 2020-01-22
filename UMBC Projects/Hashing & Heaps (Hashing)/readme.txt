Date: 12/2019
Project 5: Hashing & Heaps


The objectives of this programming assignment are:

- To implement a heap and a hash table.
- To implement linear probing to handle hash collisions.
- To practice writing templated classes.



Compilation is done through the makefile on a Unix system.



Background:

For this project, you have to complete two templated classes:

heap.h: the Heap class is a templated, vector-based heap implementation. This is a straight-forward implementation of a heap. Since it uses a vector rather than a C-style array to store the heap, you will not need to write a copy constructor, assignment operator, or destructor.

hash.h: the HashTable class is a hash table implementation with a wrinkle — each bucket in the table is a heap! Collisions will be handled by linear probing. The array to store the hash table is a dynamically-allocated array (of heaps), so you will need to write a copy constructor, assignment operator, and destructor for this class.

Why would you ever want to build such a thing? I'm not sure you would, but here is a made-up application. Suppose you are a donut baker, and you distribute donuts to many different shops. You have a large number of donut types that you can bake — glazed, cinnamon, boston cream, bavarian cream, sprinkle, etc. — and lots of customers. Some of the customers are more important to you because they buy more donuts and always pay on time. You would like to record all your orders in the following way:

First, you want to be able to search by donut type.
Then, given the donut type, you always want to process the highest priority order first.
So, the donut type is the key for hashing purposes. All orders for a particular type will be stored in the same bucket, but the bucket will be a max-heap so that you can always retrieve the highest priority order quickly.
Once you see how the donut example works, it's not too difficult to think of others. Suppose you want to track the repair priority of highway bridges. You want to search by highway name — US50, I97, I695, MD32, etc. — and, given the highway name, retrieve the bridge that is most in need of repair. The highway name is the hash key, and each bucket of the hash table is a max-heap using based on the repair priorities.

Since the Heap and HashTable classes are templated, it is easy to test them with either of the two examples given, or an example of your own. See the comments in hash.h for the requirements that the template class must satisfy and donut.h for an implementation of the donut example.



Assignment:

Your assignment is to complete the templated class Heap in heap.h and the templated class HashTable in hash.h. The classes must be implemented entirely in their .h files: there will be no separate .cpp files.

You may have been taught to implement templated files differently, creating separate .h and .cpp files that include each other and are both guarded, but that is not how we are doing it for this project.

The HashTable class uses the Heap class, so it is recommended that you implement and test Heap first. A sample driver is provided that demonstrates use of the HashTable class with a Donut object. The driver does not perform thorough testing. As always, you are responsible for thoroughly testing your program. It is particularly important that your code run without segmentation faults, memory leaks, or memory errors.



Additional Requirements:

Requirement: Both templated classes (Heap and HashTable) must be implemented in their respective .h files. There are no separate .cpp files for Heap and HeapTable.

Requirement: Private helper functions may be added to either templated class; however, they must be declared in the private section of the class declaration.

Requirement: Heap must implement a vector-based max-heap data structure. It must not use the index zero element of the vector; heap elements are stored at indices 1, 2, ..., size(). The template class T must provide priorities through a priority() function that returns an unsigned integer.

Requirement: If readTop() or removeTop() is called on an empty heap, a range_error exception must be thrown.

Requirement: The heap insert() and removeTop() methods must run in O(log n) time.

Requirement: HashTable must implement a hash table in which each buckets is a Heap object. Each bucket contains objects with the same key value, organized in a max-heap by priority. The template class T must provide the key value for an object through a key() function that returns a string.

Requirement: The hash table size and hash function are specified in the constructor call. The table must be dynamically allocated in the constructor.

Requirement: Hash collisions must be resolved by linear probing.

Requirement: Hash indices must be computed by applying the hash function to the key value and reducing the hash output modulo the table size (i.e. the MOD compression function).

Requirement: For the HashTable class, a destructor, copy constructor, and assignment operator must be implemented.

Requirement: Basic hash operations on a sparsely populated table (small load factor) must run in constant time. In particular, insertion to an empty table and retrieval from a table with only one element must run in constant time.



Implementation Notes:

The _used variable and used() function of the Heap class are provided to support linear probing in HashTable. Recall that, with linear probing, buckets that have never held data must be treated differently than buckets that once held data that has since been deleted.
