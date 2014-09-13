#ifndef QUEUE_H_
#define QUEUE_H_
#include <exception>
class DequeueException:public std::exception
{

public:
	DequeueException(char* what):m_What(what)
	{

	}
	char* m_What;
	virtual const char* what() const throw()
	{
		return m_What;
	}
};
class EnqueueException:public std::exception
{
public:
	EnqueueException(char * what):m_What(what)
	{

	}
	char* m_What;
	virtual const char* what() const throw()
	{
		return m_What;
	}
};
enum QueueType
{
	QueueType_FINITE = 0,
	QueueType_INFINITE
};
template <typename T>
class Node
{
public:
	Node():next(0),prev(0){}
	~Node(){}
	T data;
	Node* next, *prev;
};
template <typename T>
class Queue
{
public:
	Queue():m_Type(QueueType_INFINITE),m_Capacity(DEFAULT_SIZE),m_Size(0),m_Head(0),m_Tail(0)
	{
	}
	Queue(QueueType type):m_Type(type),m_Capacity(DEFAULT_SIZE),m_Size(0),m_Head(0),m_Tail(0)
	{
	}
	Queue(QueueType type, unsigned int capacity):m_Type(type), m_Capacity(capacity),m_Size(0),m_Head(0),m_Tail(0)
	{
	}
	unsigned int size(){return m_Size;}
	unsigned int capacity(){return m_Capacity;}
	bool enqueue(T data)
	{
		if(m_Type != QueueType_INFINITE && m_Size == m_Capacity)
		{
			EnqueueException e("Capacity exceeded.");
			throw e;
			return false;
		}
		Node<T> *new_node = new Node<T>();
		new_node->data = data;
		if(m_Head == 0)
		{
			m_Head = new_node;
			m_Tail = new_node;
			m_Size ++;
		}
		else
		{
			m_Tail->next = new_node;
			m_Tail = m_Tail->next;
			m_Size ++;
		}
		return true;
	}
	T dequeue()
	{
		T data;
		if(m_Head == m_Tail == 0)
		{
			DequeueException e("Dequeue called on empty queue.");
			throw e;
		}
		if(m_Head == m_Tail)
		{
			data = m_Head->data;
			Node<T> *temp = m_Head;
			m_Head = 0;
			m_Tail = 0;
			delete temp;
			m_Size--;
		}
		else
		{
			data = m_Head->data;
			Node<T> *temp = m_Head;
			m_Head = m_Head->next;
			delete temp;
			m_Size --;

		}
		return data;
	}
	bool is_empty()
	{
		return m_Size == 0;
	}
	bool is_full()
	{
		if(m_Type == QueueType_FINITE)
		{
			return m_Size == m_Capacity;
		}
		return false;
	}

private:

	QueueType m_Type;
	static unsigned int DEFAULT_SIZE;
	unsigned int m_Capacity, m_Size;
	Node<T> *m_Head, *m_Tail;
};
template <typename T>
unsigned int Queue<T>::DEFAULT_SIZE = 100;



#endif /* QUEUE_H_ */
