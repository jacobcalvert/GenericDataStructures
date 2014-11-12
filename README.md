This is a collection of generic templated data structures. The reason? Just because. 
I am attempting to go back and doxygen-style comment the code as well as document it here.
<br>
<br>

UPDATE!!!
<br> 

Doxygen stuff is now in the repo under the 'html' folder.

Structures Done
--------------------
* Queue
* Stack
* List
* MinHeap
* Binary Search Tree
* HashTable

Structures Planned
-----------------------
* MaxHeap
* Red-Black Tree (this one is taking a HOT minute...)
* Graph



The planned list will probably grow as I see more interesting things I want to add to it. 


KNOWN BUGS / ISSUES
-----------------------
* in the heap structure, I have not tested if it is reusable as far as multipt insert and remove mins interleaved
* remove() is not implemented for the BST nor is height();
* I'm sure I will find more!

CLOSED BUGS / ISSUES
------------------------
* I'm converting the char* in the exception generation code to std::string so the compiler will shut up with deprecation warnings [closed 10/15/2014]
* Removed all the compiler warnings at this moment [closed 10/15/2014]
* Added copy constructors and assignment operarators to all the "done" classes. [closed 11/12/2014]
* Fixed destructor bug in the HashTable where I was not releasing memory [closed 11/12/2014]




