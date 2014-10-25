/**
 * @file   Stack.h
 * @Author Jacob Calvert (jacob+info@jacobncalvert.com)
 * @date   September, 2014
 * @brief  Implementation of a link-based stack.
 *
 * This stack implementation is based on linked nodes which guarantees constant time
 * operations for certain things. By holding a reference to the size of the stack,
 * we can enforce certain restrictions and provide extra functions such as stack waiting via is_full()
 *
 * The code has exceptions for illegal operations on the standard ADT Stack.
 */
#ifndef STACK_H_
#define STACK_H_
#include "GenericDefinitions.h"
#include <exception>
#include <string>
class PushException:public std::exception
{

public:
	PushException(std::string what):m_What(what)
	{

	}
	virtual ~PushException() throw()
	{
	}
	std::string m_What;
	virtual const char* what() const throw()
	{
		return m_What.c_str();
	}
};
class PopException:public std::exception
{
public:
	PopException(std::string what):m_What(what)
	{

	}
	virtual ~PopException() throw()
	{
	}
	std::string m_What;
	virtual const char* what() const throw()
	{
		return m_What.c_str();
	}
};
class PeekException:public std::exception
{
public:
	PeekException(std::string what):m_What(what)
	{

	}
	virtual ~PeekException()throw()
	{

	}
	std::string m_What;
	virtual const char* what() const throw()
	{
		return m_What.c_str();
	}
};
enum StackType
{
	StackType_INFINTE = 0,
	StackType_FINITE = 1
};
template <typename T>
class Stack
{
public:
	/**
	 * Stack constructor.
	 * Constructs an infinite stack.
	 */
	Stack():m_Head(0),m_Tail(0),m_Size(0),m_Capacity(DEFAULT_CAPACITY),m_Type(StackType_INFINTE)
	{}
	/**
	 * Stack constructor.
	 * Constructs a stack of the specified type with the capacity set to DEFAULT_CAPACITY
	 * @param type the type of stack
	 * @see StackType
	 */
	Stack(StackType type):m_Head(0),m_Tail(0),m_Size(0),m_Capacity(DEFAULT_CAPACITY),m_Type(type)
	{}
	/**
	 * Stack constructor.
	 * Constructs a stack of specified type and capacity
	 * @param type the type of stack
	 * @see StackType
	 */
	Stack(StackType type, unsigned int capacity):m_Head(0),m_Tail(0),m_Size(0),m_Capacity(capacity),m_Type(type)
	{}
	/**
	 * Destructor.
	 * Nothing to see here. Simply destroys the nodes.
	 */
	~Stack()
	{
		this->empty();
	}
	/**
	 * returns true if the stack is full and finite false otherwise
	 */
	bool is_full()
	{
		if(m_Type == StackType_FINITE && m_Size == m_Capacity)
		{
			return true;
		}
		return false;
	}
	/**
	 * returns true if the stack size is zero
	 */
	bool is_empty()
	{
		return m_Size == 0;
	}
	/**
	 * returns the size of the stack
	 * NOTE: size is not the same as capacity
	 */
	unsigned int size(){return m_Size;}
	/**
	 * returns the capacity of the stack.
	 * NOTE: size is not the same as capacity
	 */
	unsigned int capacity(){return m_Capacity;}
	/**
	 * empties the stack via repeated calls to pop
	 * @see pop()
	 */
	void empty()
	{
		while(!this->is_empty())
		{
			this->pop();
		}
	}
	/**
	 * shows the top of the stack without popping it
	 */
	T peek()
	{
		if((m_Head == m_Tail) && m_Head == 0)
		{
			PeekException e("Peek called on empty stack");
		}
		return m_Head->data;
	}
	/**
	 * adds a value to the top of the stack
	 * @param data the data being added to the stack top
	 * @see pop()
	 */
	bool push(T data)
	{
		if (m_Type == StackType_FINITE && m_Size == m_Capacity)
		{
			PushException e("Stack space exceeded.");
			throw e;
			return false; //TODO: exception
		}
		Node<T>* new_node = new Node<T>();
		new_node->data = data;
		if(m_Head == 0)
		{
			m_Head = new_node;
			m_Tail = new_node;
			m_Size ++;

		}
		else
		{
			new_node->next = m_Head;
			m_Head = new_node;
			m_Size++;
		}
		return true;
	}
	/**
	 * returns the top item and removes it from the stack
	 * @see peek()
	 */
	T pop()
	{
		T data;
		if((m_Head == m_Tail) && m_Head == 0)
		{
			PopException e("Pop called on empty stack.");
			throw e;
		}
		else
		{
			if(m_Size == 1)
			{
				data = m_Head->data;
				Node<T>* temp = m_Head;
				m_Head = 0;
				m_Tail = 0;
				delete temp;
			}
			else
			{
				Node<T>* temp = m_Head;
				data = temp->data;
				m_Head = m_Head->next;


			}
			m_Size --;

		}


		return data;
	}
	bool operator!=(const Stack<T> &rhs)
	{
		return !(*this == rhs);
	}
	bool operator==(const Stack<T> &rhs)
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
	Node<T>* m_Head, *m_Tail;
	static unsigned int DEFAULT_CAPACITY;
	unsigned int m_Size, m_Capacity;
	StackType m_Type;
};
template <typename T>
unsigned int Stack<T>::DEFAULT_CAPACITY = 100;



#endif /* STACK_H_ */
