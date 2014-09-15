#include "tests.h"
#include "stdio.h"
#include "Queue.h"
#include "Stack.h"
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

	return true;
}
bool test_all()
{
	printf("Test Stack: %s\n",  test_stack()?"PASS":"FAIL");
	printf("Test Queue: %s\n",  test_queue()?"PASS":"FAIL");
}
