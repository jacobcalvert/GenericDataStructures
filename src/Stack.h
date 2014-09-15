#ifndef STACK_H_
#define STACK_H_
#include "GenericDefinitions.h"
#include <exception>
class PushException:public std::exception
{

public:
	PushException(char* what):m_What(what)
	{

	}
	char* m_What;
	virtual const char* what() const throw()
	{
		return m_What;
	}
};
class PopException:public std::exception
{
public:
	PopException(char * what):m_What(what)
	{

	}
	char* m_What;
	virtual const char* what() const throw()
	{
		return m_What;
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
	Stack():m_Head(0),m_Tail(0),m_Size(0),m_Capacity(DEFAULT_CAPACITY),m_Type(StackType_INFINTE)
	{}
	Stack(StackType type):m_Head(0),m_Tail(0),m_Size(0),m_Capacity(DEFAULT_CAPACITY),m_Type(type)
	{}
	Stack(StackType type, unsigned int capacity):m_Head(0),m_Tail(0),m_Size(0),m_Capacity(capacity),m_Type(type)
	{}
	bool is_full()
	{
		if(m_Type == StackType_FINITE && m_Size == m_Capacity)
		{
			return true;
		}
		return false;
	}
	bool is_empty()
	{
		return m_Size == 0;
	}
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
	T pop()
	{
		T data;
		if((m_Head == m_Tail) && m_Head == 0)
		{
			//TODO: raise exc
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
private:
	Node<T>* m_Head, *m_Tail;
	static unsigned int DEFAULT_CAPACITY;
	unsigned int m_Size, m_Capacity;
	StackType m_Type;
};
template <typename T>
unsigned int Stack<T>::DEFAULT_CAPACITY = 100;



#endif /* STACK_H_ */
