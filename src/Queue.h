#ifndef QUEUE_H_
#define QUEUE_H_
#include "GenericDefinitions.h"
#include <exception>
#include <string>
class DequeueException:public std::exception
{

public:
	DequeueException(std::string what):m_What(what)
	{

	}
	virtual ~DequeueException() throw()
	{

	}
	std::string m_What;
	virtual const char* what() const throw()
	{
		return m_What.c_str();
	}
};
class EnqueueException:public std::exception
{
public:
	EnqueueException(std::string what):m_What(what)
	{

	}
	virtual ~EnqueueException() throw()
	{

	}
	std::string m_What;
	virtual const char* what() const throw()
	{
		return m_What.c_str();
	}
};
enum QueueType
{
	QueueType_FINITE = 0,
	QueueType_INFINITE
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
	~Queue()
	{
		this->empty();
	}
	unsigned int size(){return m_Size;}
	unsigned int capacity(){return m_Capacity;}
	void empty()
	{
		while(!this->is_empty())
		{
			this->dequeue();
		}
	}
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
		if((m_Head == m_Tail) && m_Head == 0)
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
	bool operator!=(const Queue<T> &rhs)
	{
		return !(*this == rhs);
	}
	bool operator==(const Queue<T> &rhs)
	{
		if(rhs.m_Size != m_Size)
		{
			return false;
		}
		else
		{
			Node<T> *p = m_Head, *q = rhs.m_Head;
			for(unsigned int i = 0; i < m_Size; i ++)
			{
				if(p->data != q->data)
				{
					return false;
				}
				else
				{
					p = p->next;
					q = q->next;
				}
			}
		}
		return true;
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
