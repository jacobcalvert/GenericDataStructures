/**
 * @file   Queue.h
 * @Author Jacob Calvert (jacob+info@jacobncalvert.com)
 * @date   September, 2014
 * @brief  Implementation of a link-based queue.
 *
 * This queue implementation is based on linked nodes which guarantees constant time
 * operations for certain things. By holding a reference to the size of the queue,
 * we can enforce certain restrictions and provide extra functions such as queue waiting via is_full()
 *
 * The code has exceptions for illegal operations on the standard ADT Queue.
 */
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
	/**
	 * Queue constructor.
	 * Constructs an infinite queue.
	 */
	Queue():m_Type(QueueType_INFINITE),m_Capacity(DEFAULT_SIZE),m_Size(0),m_Head(0),m_Tail(0)
	{
	}
	/**
	 * Queue constructor.
	 * Constructs a queue of the specified type with the capacity set to DEFAULT_SIZE
	 * @param type the type of queue
	 * @see QueueType
	 */
	Queue(QueueType type):m_Type(type),m_Capacity(DEFAULT_SIZE),m_Size(0),m_Head(0),m_Tail(0)
	{
	}
	/**
	 * Queue constructor.
	 * Constructs a queue of specified type and capacity
	 * @param type the type of queue
	 * @see QueueType
	 */
	Queue(QueueType type, unsigned int capacity):m_Type(type), m_Capacity(capacity),m_Size(0),m_Head(0),m_Tail(0)
	{
	}
	/**
	 * Destructor.
	 * Nothing to see here. Simply destroys the nodes.
	 */
	~Queue()
	{
		this->empty();
	}
	/**
	 * returns the size of the queue
	 * NOTE: size is not the same as capacity
	 */
	unsigned int size(){return m_Size;}
	/**
	 * returns the capacity of the queue.
	 * NOTE: size is not the same as capacity
	 */
	unsigned int capacity(){return m_Capacity;}
	/**
	 * empties the queue via repeated calls to dequeue
	 * @see dequeue()
	 */
	void empty()
	{
		while(!this->is_empty())
		{
			this->dequeue();
		}
	}
	/**
	 * enqueues some data into the queue
	 * Will throw an exception if queue is finite and the size > capacity
	 * @param data data to be enqueued
	 */
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
	/**
	 * dequeues and returns an item from the queue
	 */
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
	/**
	 * returns true if empty
	 */
	bool is_empty()
	{
		return m_Size == 0;
	}
	/**
	 * only valid if the queue type is finite, returns true if the queue is full
	 *
	 */
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
