#include "Queue.h"
#include "stdio.h"
int main()
{
	Queue<int>q(QueueType_FINITE, 10);
	int i = 0;
	while(i<10)
	{
		q.enqueue(i++);
	}
	while(1)
	{
		q.dequeue();
	}
	return 0;
}
