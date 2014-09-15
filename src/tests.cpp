#include "tests.h"
#include "stdio.h"
#include "Queue.h"
#include "Stack.h"
#include "List.h"
#include <string>
#include <exception>
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
	int lim = 100000;
	Queue<int> q2(QueueType_FINITE, lim);
	int i = 0;
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
	int lim = 100000;
	Stack<int> s2(StackType_FINITE, lim);
	int i = 0;
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
	int i = 0, lim = 1000;
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
		if(i != l[i])
		{
			return false;
		}
		i++;
	}
	i = 0;
	while(--i > (-lim))
	{
		if(l[i] != lim + i)
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
		l.remove(-1);
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
		if(l[i] != i)
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
	B.remove(-1);
	if(A == B)
	{
		return false;
	}
	B.append(0);
	if(A==B)
	{
		return false;
	}
	return true;
}
bool test_all()
{
	printf("Test Stack: %s\n",  test_stack()?"PASS":"FAIL");
	printf("Test Queue: %s\n",  test_queue()?"PASS":"FAIL");
	printf("Test List:  %s\n",  test_list()?"PASS":"FAIL");
}
