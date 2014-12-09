#include "tests.h"
#include "stdio.h"
#include "Queue.h"
#include "Stack.h"
#include "List.h"
#include "Heap.h"
#include "RedBlackTree.h"
#include "BinarySearchTree.h"
#include "HashTable.h"
#include <string>
#include <exception>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>

bool test_tuple()
{
	return true;
}

bool test_queue()
{
	Queue<int> q1;
	for(int i = 1; i<=10; i++)
	{
		q1.enqueue(i);
	}
	int cs = 0;
	while(!q1.is_empty())
	{
		cs += q1.dequeue();
	}
	if(cs != 55)
	{
		return false;
	}
	unsigned int lim = 100000;
	Queue<int> q2(QueueType_FINITE, lim);
	unsigned int i = 0;
	while(i++ < lim)
	{
		q2.enqueue(i);
	}
	if(q2.size() != lim)
	{
		return false;
	}
	if(q2.capacity() != lim)
	{
		return false;
	}
	while(!q2.is_empty())
	{
		q2.dequeue();
	}

	i = 0;
	bool caught = false;
	try
	{
		while(i < lim + lim)
		{
			i++;
			q2.enqueue(i);
		}
	}
	catch(std::exception& e)
	{
		caught = true;
	}
	if(!caught)
	{
		return false;
	}
	Queue<char> q3;
	q3.enqueue('J');q3.enqueue('A');
	q3.enqueue('C');
	q3.enqueue('O');
	q3.enqueue('B');
	std::string name;
	while(!q3.is_empty())
	{
		name += q3.dequeue();
	}
	if(name != "JACOB")
	{
		return false;
	}
	Queue<int> A, B;
	i = 0;
	while(i < 10)
	{
		A.enqueue(i);
		B.enqueue(i);
		i++;
	}
	if(A != B)
	{
		return false;
	}

	return true;
}
bool test_maxheap()
{
	MaxHeap<int> maxheap;
	int lim = 1000;
	for(int i = 0;i < lim; i++)
	{
		maxheap.insert(rand() % lim  + (rand() < (RAND_MAX/8)?-lim/10:lim));
	}
	int *max_sort = new int[maxheap.size()];
	int i = 0;
	while(maxheap.size())
	{
		max_sort[i++] = maxheap.remove_max();
	}
	i = 1;
	for(int i = 1; i < lim; i++)
	{
		if(max_sort[i] > max_sort[i-1])return false;
	}
	return true;
}
bool test_minheap()
{
	srand(time(NULL));
	MinHeap<long long> minheap;
	int lim = 1000;

	minheap.insert(12);minheap.insert(15);minheap.insert(11);minheap.insert(1);minheap.insert(12);

	if(DEBUG)printf("heap find (15) = %s\n",minheap.find(15)?"TRUE":"FALSE");
	for(long long i = 0; i < lim; i++)
	{
		minheap.insert(rand() % lim  + (rand() < (RAND_MAX/8)?-lim/10:lim));
	}
	if(DEBUG)
	{
		printf("First 15 of 1000 sorted is = [");

		for(long long i = 0; i < 15; i++)
		{
			printf("%lld,", minheap.remove_min());
		}
		printf("...]\n");

		printf("get nth = %lld\n", minheap.get_nth(15));
	}

	MinHeap<int> heap2;
	for(int i = 0; i < 1000; i ++)
	{
		heap2.insert(i);
		while(heap2.size()>50)heap2.remove_min();
	}

	return true;
}
bool test_stack()
{
	Stack<int> s1;
	for(int i = 1; i<=10; i++)
	{
		s1.push(i);
	}
	int cs = 0;
	while(!s1.is_empty())
	{
		cs += s1.pop();
	}
	if(cs != 55)
	{
		return false;
	}
	unsigned int lim = 100000;
	Stack<int> s2(StackType_FINITE, lim);
	unsigned int i = 0;
	while(i++ < lim)
	{
		s2.push(i);

	}
	if(s2.size() != lim)
	{
		return false;
	}
	if(s2.capacity() != lim)
	{
		return false;
	}
	while(!s2.is_empty())
	{
		s2.pop();
	}
	bool caught = false;
	i = 0;
	try
	{
		while(i < lim + lim)
		{
			i++;
			s2.push(i);
		}
	}
	catch(std::exception& e)
	{
		caught = true;
	}
	if(!caught)
	{
		return false;
	}
	Stack<int> A, B;
	i = 0;
	while(i < 10)
	{
		A.push(i);
		B.push(i);
		i++;
	}
	if(A != B)
	{
		return false;
	}
	Stack<int> C;
	C.push(1);
	if(C.peek() != 1)
	{
		return false;
	}
	C.push(2);
	if(C.peek()!= 2)
	{
		return false;
	}
	C.pop();
	if(C.peek() != 1)
	{
		return false;
	}
	return true;
}
bool test_list()
{
	List<int> l;
	unsigned int i = 0, lim = 1000;
	while(i < lim)
	{
		l.append(i);
		i++;
	}
	if(l.size() != lim)
	{
		return false;
	}
	i = 0;
	while(i < l.size())
	{
		if(i != (unsigned int) l[i])
		{
			return false;
		}
		i++;
	}
	i = 0;
	while(--i > (-lim))
	{
		if((unsigned int)l[i] != lim + i)
		{
			return false;
		}
	}
	i = 0;
	while (i < l.size())
	{
		l.replace(i, 0);
		i++;

	}
	i = 0;
	while(i < l.size())
	{
		if(l[i] != 0)
		{
			return false;
		}
		i++;
	}
	while(l.size() > 100)
	{
		l.remove_at(-1);
	}
	i = 0;
	while (i < l.size())
	{
		l.replace(i, i);
		i++;

	}
	i = 0;
	while(i < l.size())
	{
		if((unsigned int) l[i] != i)
		{
			return false;
		}
		i++;
	}

	List<int> A, B;
	i = 0;

	while(i < lim)
	{
		A.append(i);
		B.append(i);
		i++;
	}
	if((A != B))
	{
		return false;
	}
	B.remove_at(-1);
	if(A == B)
	{
		return false;
	}
	B.append(0);
	if(A==B)
	{
		return false;

	}

	List <int> C;
	i = 1;
	while(i <= lim){C.append(i++);}
	long long n = (lim*(lim + 1))/2, sum = 0;
	C.remove(1);
	C.remove(2);
	for(long long j = 0; j < C.size(); j++)
	{
		sum += C[j];
	}
	if(n - 3 !=  sum)return false;
	return true;

}
bool test_redblack()
{
	RedBlackTree<int> rbt;
	int lim = 1000;
	srand(time(NULL));
	for(int i = 0; i < lim; i++)
	{
		rbt.insert((i + lim ) % lim);
	}

	int *sorted = rbt.inorder();
	printf("\n");
	for(int i = 0; i < 15; i++)
	{
		printf("%d", sorted[i]);
	}
	printf("\n");
	return true;
}
bool test_bst()
{
	BinarySearchTree<int> bst;
	int lim = 1024, i;
	srand(time(NULL));
	for(i = 0; i < lim; i ++)
	{
		bst.insert(rand() % lim + 1);
	}
	if(bst.size() != lim)return false;
	int *sorted = bst.inorder();
	for(i = 1; i < lim; i++ )
	{
		if(sorted[i-1] > sorted[i]){return false;}
	}

	int n = sorted[rand() % (lim/2)];
	if(!bst.find(n)) return false;
	//bst.remove(n);
	sorted = bst.inorder();
	for(i = 1; i < bst.size(); i++ )
	{
		if(sorted[i-1] > sorted[i]){return false;}
	}
	BinarySearchTree<int> bst2;
	bst2.insert(6);
	bst2.insert(3);
	bst2.insert(8);
	bst2.insert(2);
	bst2.insert(0);
	bst2.insert(10);
	bst2.insert(5);
	bst2.insert(1);
	bst2.insert(4);
	bst2.insert(7);
	bst2.insert(9);


	i = 0;
	while(bst.size())
	{
		bst.remove(sorted[i++]);
	}
	return true;
}
bool test_hashtable()
{
	HashTable<int, char> ht;
	for(int i = 0; i < 1000; i++)
	{
		ht.set(i, (char)i);
	}
	for(int i = 0; i < 1000; i++)
	{
		ht.remove(i);
	}
	if(ht.size() != 0)
	{
		return false;
	}
	HashTable<int, int> ht2;
	for(int i = 0; i < 1000; i++)
	{
		ht2.set(0, i);
	}
	if(ht2.size() != 1)return false;

	HashTable<int, int> ht3;
	ht3[0] = 0;
	ht3[0] = 1;

	if(ht3[0] != 1)return false;


	return true;
}
void character_histogram()
{
	HashTable<char, long long> ht;
	std::ifstream input("/home/jacob/Documents/Eclipse Workspace/C++/GenericDataStructures/test_files/PG-MobyDick.txt");
	char c;
	if(input.is_open())
	{
		while(input.get(c))
		{
			if(ht.contains(c))
			{
				ht[c]+=1;
			}
			else
			{
				ht[c] = 1;
			}
		}
	}
	ht.remove('c');
	HashTable<char, long long>::iterator it = *ht.begin();
	while(it.pos() < it.end())
	{
		//std::cout<<"'"<< it.key()<<"'" << "=>"<< it.value() << std::endl;
		it++;
	}
	it--;
	while(it.pos() >= it.begin())
	{
		//std::cout<<"'"<< it.key()<<"'" << "=>"<< it.value() << std::endl;
		it--;
	}

	MinHeap<huff_node*> heap1;
	HashTable<char, long long>::iterator it2 = *ht.begin();
	while(it2.pos() < it2.end())
	{
		huff_node * node = new huff_node;
		node->c = it2.key();
		node->freq = it2.value();
		node->is_leaf = true;
		heap1.insert(node);
		it2++;
	}

	while(heap1.size() > 2)
	{
		huff_node *left = heap1.remove_min(), *right = heap1.remove_min(), *new_node= new huff_node;
		new_node->is_leaf = false;
		new_node->freq = left->freq + right->freq;
		new_node->left = left;
		new_node->right = right;
		heap1.insert(new_node);
	}
	huff_node *left = heap1.remove_min(), *right = heap1.remove_min(), *root= new huff_node;
	root->is_leaf = false;
	root->freq = left->freq + right->freq;
	root->left = left;
	root->right = right;
	//HashTable<char, long long>::iterator it3 = *ht.begin();
	//root is a huffman tree, could be traversed to create a compression algorithm
}
void reverse_a_list()
{
	List<int> list;
	unsigned int i = 1, lim = 20;
	for(;i<lim; i++)
	{
		list.append(i);
	}
	printf("List contains: [");
	i = 0;
	while(i < list.size()-1)
	{
		printf("%d, ", list[i]);
		i++;
	}
	printf("%d]\n", list[list.size()-1]);
	Stack<int> s1, s2;
	i = 0;
	while(i < list.size())
	{
		s1.push(list[i++]);
	}
	i = 0;
	while(!s1.is_empty())
	{
		list.replace(i++, s1.pop());
	}
	printf("List reversed: [");
	i = 0;
	while(i < list.size()-1)
	{
		printf("%d, ", list[i]);
		i++;
	}
	printf("%d]\n", list[list.size()-1]);


}
void bin_sort()
{

	long long size = 100000, lim = size;
	long long arr[size], sT, eT;
	Queue<long long> bins[lim];
	long long i = 0;
	while(i< size)
	{
		arr[i++] = rand() % lim;
		//printf("%d\n",arr[i-1]);
	}
	sT = time(NULL);
	for(long long i = 0; i < size; i++)
	{
		bins[arr[i]].enqueue(arr[i]);
	}
	long long k = 0;
	for(long long i = 0; i < lim; i ++)
	{

		while(!bins[i].is_empty())
		{
			arr[k++] = bins[i].dequeue();
			//printf("%d,",arr[k-1]);

		}

	}
	eT = time(NULL);

	printf("Sorted %lld random numbers in range [0, %lld) using bin sort and queues in %lld seconds\n", size,lim,  (eT-sT));
	printf("SAMPLE: [%lld, %lld, %lld, %lld,...\n", arr[0], arr[1], arr[2], arr[3]);
	really_long_list(arr, size);
}
void really_long_list(long long * arr, long long len)
{
	List<long long> list;
	printf("Initial list size: %d\n", list.size());
	long long i = 0;
	printf("Appending all values from sorted array to list...\n");
	while(i < len)
	{
		list.append(arr[i++]);
	}
	printf("Current list size: %d\n", list.size());
	printf("SAMPLE: [%lld, %lld, %lld, %lld,... (should match from above)\n", list[0], list[1], list[2], list[3]);
}
void functional_tests()
{
	srand(time(NULL));
	printf("FUNCTIONAL TESTS\n");
	reverse_a_list();
	bin_sort();
	character_histogram();
}
bool test_all()
{
	printf("Test Stack: %s\n",  test_stack()?"PASS":"FAIL");
	printf("Test Queue: %s\n",  test_queue()?"PASS":"FAIL");
	printf("Test List:  %s\n",  test_list()?"PASS":"FAIL");
	printf("Test MinHeap: %s\n",test_minheap()?"PASS":"FAIL");
	printf("Test MaxHeap: %s\n",test_maxheap()?"PASS":"FAIL");
	printf("Test RedBlack: %s\n", /*test_redblack()*/false?"PASS":"FAIL");
	printf("Test BST: %s\n", test_bst()?"PASS":"FAIL");
	printf("Test HashTable: %s\n",test_hashtable()?"PASS":"FAIL");
	printf("Test Tuple: %s\n",test_tuple()?"PASS":"FAIL");
	if(DEBUG)functional_tests();
	return 1;
}
