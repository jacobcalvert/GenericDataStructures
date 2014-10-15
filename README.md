This is a collection of generic templated data structures. The reason? Just because. 
I am attempting to go back and doxygen-style comment the code as well as document it here.


Structures Done
--------------------
* Queue
* Stack
* List
* MinHeap
* Binary Search Tree

Structures Planned
-----------------------
* MaxHeap
* Red-Black Tree
* ....???



The planned list will probably grow as I see more interesting things I want to add to it. 


KNOWN BUGS / ISSUES
-----------------------
* in the heap structure, I have not tested if it is reusable as far as multipt insert and remove mins interleaved
* remove() is not implemented for the BST nor is height();
* I'm sure I will find more!

CLOSED BUGS / ISSUES
------------------------
* I'm converting the char* in the exception generation code to std::string so the compiler will shut up with deprecation warnings [closed 10/15/2014]


Structures and Features
============================

Queue
--------
### Features ###
* finite and infinte sizes that are enforced in the object, set via the constructor
* exceptioned for unsupported operations (dequeue when empty etc.)
### Supported Methods ###

<table>
	<tr>
	<th>Method Name</th>
	<th>Description</th>
	</tr>
	<tr>
		<td>empty()</td>
		<td>empties the queue</td>
	</tr>
	<tr>
		<td>enqueue(data)</td>
		<td>enqueues(data) into the queue</td>
	</tr>
	<tr>
		<td>dequeue()</td>
		<td>dequeues an item</td>
	</tr>
	<tr>
		<td>is_empty()</td>
		<td>is it empty?</td>
	</tr>
	<tr>
		<td>is_full()</td>
		<td>is it full? (only valid with finite queues)</td>
	</tr>
	<tr>
		<td>== & !=</td>
		<td>performs a node-by-node comparison of the two queues</td>
	</tr>

</table>

Stack
-------------
### Features ###
* finite and infinte sizes that are enforced in the object, set via the constructor
* exceptioned for unsupported operations (pop when empty etc.)
### Supported Methods ###

<table>
	<tr>
	<th>Method Name</th>
	<th>Description</th>
	</tr>
	<tr>
		<td>pop()</td>
		<td>removes and returns the top of the stack</td>
	</tr>
	<tr>
		<td>push(data)</td>
		<td>pushed(data) onto the top of the stack</td>
	</tr>
	<tr>
		<td>peek()</td>
		<td>look at the top of the stack</td>
	</tr>
	<tr>
		<td>is_empty()</td>
		<td>is it empty?</td>
	</tr>
	<tr>
		<td>is_full()</td>
		<td>is it full? (only valid with finite stacks)</td>
	</tr>
	<tr>
		<td>== & !=</td>
		<td>performs a node-by-node comparison of the two stacks</td>
	</tr>

</table>

