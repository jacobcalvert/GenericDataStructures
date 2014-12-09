/**
 * @file   Heap.h
 * @Author Jacob Calvert (jacob+info@jacobncalvert.com)
 * @date   September, 2014
 * @brief  Implementation of a node based MinHeap structure
 *
 * The MinHeap structure is node based.
 *
 * The MaxHeap has not been implemented.
 */
#ifndef HEAP_H_
#define HEAP_H_
#include "GenericDefinitions.h"
#include <exception>
#include <string>

class GeneralHeapException:public std::exception
{

public:
	GeneralHeapException(std::string what):m_What(what)
	{

	}
	virtual ~GeneralHeapException() throw()
	{
	}
	std::string m_What;
	virtual const char* what() const throw()
	{
		return m_What.c_str();
	}
};
template <typename T>
class MaxHeap
{
public:
	/**
	 * MaxHeap constructor
	 */
	MaxHeap():m_Head(0), m_Size(0)
	{
		m_Compare = MaxHeap::default_compare;
	}
	/**
	 * copy constructor
	 */
	MaxHeap(MaxHeap<T> & rhs):m_Head(rhs.m_Head), m_Size(rhs.m_Size), m_Compare(rhs.m_Compare)
	{

	}
	/**
	 * assignment operator
	 */
	MaxHeap<T> operator=(MaxHeap<T>& rhs)
	{
		if(*this != rhs)
		{
			m_Head = rhs.m_Head;
			m_Size = rhs.m_Size;
			m_Compare = rhs.m_Compare;
		}

		return *this;
	}
	/**
	 * MaxHeap destructor
	 */
	~MaxHeap()
	{
		delete m_Head;
	}
	/**
	 * finds the value in the heap
	 * returns true if it's found, false otherwise
	 * @param data the data to search for
	 */
	bool find(T data)
	{
		bool found = false;
		found = find(data, m_Head);
		return found;
	}
	/**
	 * returns the size of the heap
	 */
	long long size(){return m_Size;}
	/**
	 * sets the comparator for the heap compare functions
	 * @param func a function pointer to the comparator function
	 */
	void set_comparator(int (*func)(T&, T&))
	{
		m_Compare = func;
	}
	/**
	 * returns the nth node in the heap
	 * @param n the node number specifier
	 */
	T get_nth(long long n)
	{
		if(n > m_Size)
		{
			GeneralHeapException e("Called get_nth(long long n) with n > heap size.");
			throw e;
		}
		else
		{
			TreeNode<T> *p = m_Head;
			while(n >=1)
			{
				int bit = n % 2;
				n/=2;
				if(bit == 1)
				{
					p = p->right;
				}
				else
				{
					p = p->left;
				}
			}
			if(!p->valid)
			{
				GeneralHeapException e("Called get_nth(long long n) and reached an invalid node!");
				throw e;
			}
			return p->data;
		}
	}
	/**
	 * inserts the data into the appropriate position in the heap
	 * @param data the data to insert
	 */
	void insert(T data)
	{
		TreeNode<T> *new_node = new TreeNode<T>;
		new_node->data = data;
		new_node->left = new TreeNode<T>;
		new_node->right = new TreeNode<T>;
		if(m_Size == 0)
		{
			m_Head = new_node;
			m_Head->parent = 0;
			m_Head->valid = true;
		}
		else
		{
			TreeNode<T> *parent = m_Head, *prev_parent = parent;
			long long k = m_Size + 1;
			while(k > 1)
			{
				int bit = k % 2;
				k /= 2;
				prev_parent = parent;
				switch(bit)
				{
					case 0:
					{
						parent = parent->left;
						break;
					}
					case 1:
					{
						parent = parent->right;
						break;
					}
				}
			}
			new_node->parent = prev_parent;
			if(!prev_parent->left->valid)
			{
				prev_parent->left = new_node;
				new_node->valid = true;
			}
			else
			{
				prev_parent->right = new_node;
				new_node->valid = true;
			}
			while(new_node->parent && m_Compare(new_node->data, new_node->parent->data) == 1)
			{
				T temp = new_node->data;
				new_node->data = new_node->parent->data;
				new_node->parent->data = temp;
				new_node = new_node->parent;

			}
		}

		m_Size++;
	}
	/**
	 * removes and returns the max element in the heap
	 */
	T remove_max()
	{
		if(m_Size == 0)
		{
			GeneralHeapException e("Called remove_max() on empty heap.");
			throw e;
		}
		T data = m_Head->data;
		TreeNode<T> *to_remove = m_Head, *prev_parent = to_remove;
		long long k = m_Size;
		while(k > 1)
		{
			int bit = k % 2;
			k /= 2;
			prev_parent = to_remove;
			switch(bit)
			{
				case 0:
				{
					to_remove = to_remove->left;
					break;
				}
				case 1:
				{
					to_remove = to_remove->right;
					break;
				}
			}
		}
		if(prev_parent->right->valid)
		{

			to_remove = prev_parent->right;
			m_Head->data = to_remove->data;
			delete to_remove;
			prev_parent->right = new TreeNode<T>;

		}
		else
		{
			to_remove = prev_parent->left;
			m_Head->data = to_remove->data;
			delete to_remove;
			prev_parent->left = new TreeNode<T>;
		}

		TreeNode<T> *p = m_Head;

		//now we heapdown;
		T temp;
		while( (p->left->valid && (m_Compare(p->left->data,p->data) == 1) )
				|| (p->right->valid && (m_Compare(p->right->data, p->data)) == 1))
		{
			TreeNode<T>* child = p->left;
			if(p->right->valid && m_Compare(p->right->data, p->left->data) == 1)
			{
				child = p->right;
			}
			temp = p->data;
			p->data = child->data;
			child->data = temp;
			p = child;
		}

		m_Size--;
		return data;
	}

private:
	static int default_compare(T &a, T &b)
	{
		if(a < b)
		{
			return -1;
		}
		else if(a ==  b)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}

	bool find(T data, TreeNode<T> *p)
	{
		if(!p->valid)
		{
			return false;
		}
		else
		{
			if(p->data == data)
			{
				return true;
			}
			else
			{
				return find(data, p->left) || find(data, p->right);
			}

		}
	}

	TreeNode<T>* m_Head;
	long long m_Size;
	int (*m_Compare)(T&, T&);

};
template <typename T>
class MinHeap
{
public:
	/**
	 * MinHeap constructor
	 */
	MinHeap():m_Head(0), m_Size(0)
	{
		m_Compare = default_compare;
	}
	/**
	 * copy constructor
	 */
	MinHeap(MinHeap<T> & rhs):m_Head(rhs.m_Head), m_Size(rhs.m_Size), m_Compare(rhs.m_Compare)
	{

	}
	/**
	 * assignment operator
	 */
	MinHeap<T> operator=(MinHeap<T>& rhs)
	{
		if(*this != rhs)
		{
			m_Head = rhs.m_Head;
			m_Size = rhs.m_Size;
			m_Compare = rhs.m_Compare;
		}

		return *this;
	}
	/**
	 * MinHeap destructor
	 */
	~MinHeap()
	{
		delete m_Head;
	}
	/**
	 * finds the value in the heap
	 * returns true if it's found, false otherwise
	 * @param data the data to search for
	 */
	bool find(T data)
	{
		bool found = false;
		found = find(data, m_Head);
		return found;
	}
	/**
	 * inserts the data into the appropriate position in the heap
	 * @param data the data to insert
	 */
	void insert(T data)
	{
		TreeNode<T> *new_node = new TreeNode<T>;
		new_node->data = data;
		new_node->left = new TreeNode<T>;
		new_node->right = new TreeNode<T>;
		if(m_Size == 0)
		{
			m_Head = new_node;
			m_Head->parent = 0;
			m_Head->valid = true;
		}
		else
		{
			TreeNode<T> *parent = m_Head, *prev_parent = parent;
			long long k = m_Size + 1;
			while(k > 1)
			{
				int bit = k % 2;
				k /= 2;
				prev_parent = parent;
				switch(bit)
				{
					case 0:
					{
						parent = parent->left;
						break;
					}
					case 1:
					{
						parent = parent->right;
						break;
					}
				}
			}
			new_node->parent = prev_parent;
			if(!prev_parent->left->valid)
			{
				prev_parent->left = new_node;
				new_node->valid = true;
			}
			else
			{
				prev_parent->right = new_node;
				new_node->valid = true;
			}
			while(new_node->parent && m_Compare(new_node->data, new_node->parent->data) == -1)
			{
				T temp = new_node->data;
				new_node->data = new_node->parent->data;
				new_node->parent->data = temp;
				new_node = new_node->parent;

			}
		}

		m_Size++;
	}
	/**
	 * removes the minimum item from the heap
	 * also restores heap order
	 */
	T remove_min()
	{
		if(m_Size == 0)
		{
			GeneralHeapException e("Called remove_min() on empty heap.");
			throw e;
		}
		T data = m_Head->data;
		TreeNode<T> *to_remove = m_Head, *prev_parent = to_remove;
		long long k = m_Size;
		while(k > 1)
		{
			int bit = k % 2;
			k /= 2;
			prev_parent = to_remove;
			switch(bit)
			{
				case 0:
				{
					to_remove = to_remove->left;
					break;
				}
				case 1:
				{
					to_remove = to_remove->right;
					break;
				}
			}
		}
		if(prev_parent->right->valid)
		{

			to_remove = prev_parent->right;
			m_Head->data = to_remove->data;
			delete to_remove;
			prev_parent->right = new TreeNode<T>;

		}
		else
		{
			to_remove = prev_parent->left;
			m_Head->data = to_remove->data;
			delete to_remove;
			prev_parent->left = new TreeNode<T>;
		}

		TreeNode<T> *p = m_Head;

		//now we heapdown;
		T temp;
		while( (p->left->valid && (m_Compare(p->left->data,p->data) == -1) )
				|| (p->right->valid && (m_Compare(p->right->data, p->data)) == -1))
		{
			TreeNode<T>* child = p->left;
			if(p->right->valid && m_Compare(p->right->data, p->left->data) == -1)
			{
				child = p->right;
			}
			temp = p->data;
			p->data = child->data;
			child->data = temp;
			p = child;
		}

		m_Size--;
		return data;
	}
	/**
	 * returns the size of the heap
	 */
	long long size(){return m_Size;}
	/**
	 * sets the comparator for the heap compare functions
	 * @param func a function pointer to the comparator function
	 */
	void set_comparator(int (*func)(T&, T&))
	{
		m_Compare = func;
	}
	/**
	 * returns the nth node in the heap
	 * @param n the node number specifier
	 */
	T get_nth(long long n)
	{
		if(n > m_Size)
		{
			GeneralHeapException e("Called get_nth(long long n) with n > heap size.");
			throw e;
		}
		else
		{
			TreeNode<T> *p = m_Head;
			while(n >=1)
			{
				int bit = n % 2;
				n/=2;
				if(bit == 1)
				{
					p = p->right;
				}
				else
				{
					p = p->left;
				}
			}
			if(!p->valid)
			{
				GeneralHeapException e("Called get_nth(long long n) and reached an invalid node!");
				throw e;
			}
			return p->data;
		}
	}
	/**
	 * merges heap a and b together and returns the resulting heap
	 * @param a the first heap
	 * @param b the second heap
	 */
	MinHeap<T> merge(MinHeap<T> &a, MinHeap<T> &b)
	{
		return a + b;
	}
	/**
	 * returns a sorted array from the heap items
	 */
	T* get_sorted_array()
	{
		T* arr = new T[m_Size];
		MinHeap<T> temp;
		long long i = 0;
		while(this->size())
		{
			T tempd = this->remove_min();
			temp->insert(tempd);
			arr[i++] =tempd;
		}
		while(temp.size())
		{
			this->insert(temp.remove_min());
		}
		return arr;
	}
private:
	static int default_compare(T &a, T &b)
	{
		if(a < b)
		{
			return -1;
		}
		else if(a ==  b)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}

	bool find(T data, TreeNode<T> *p)
	{
		if(!p->valid)
		{
			return false;
		}
		else
		{
			if(p->data == data)
			{
				return true;
			}
			else
			{
				return find(data, p->left) || find(data, p->right);
			}

		}
	}

	TreeNode<T>* m_Head;
	long long m_Size;
	int (*m_Compare)(T&, T&);
};
template <typename T>
MinHeap<T> operator+(const MinHeap<T> &h1, const MinHeap<T> &h2)
	{
		MinHeap<T> new_heap;

		while(h1.size() || h2.size())
		{
			if(h1.size())
			{
				new_heap.insert(h1.remove_min());
			}
			if(h2.size())
			{
				new_heap.insert(h2.remove_min());
			}

		}

		return new_heap;
	}


#endif /* HEAP_H_ */
