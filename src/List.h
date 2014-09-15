#ifndef LIST_H_
#define LIST_H_
#include <exception>
#include "stdio.h"
class IndexException:public std::exception
{

public:
	IndexException(char* what):m_What(what)
	{

	}
	char* m_What;
	virtual const char* what() const throw()
	{
		return m_What;
	}
};
template <typename T>
class List
{
public:
	List():m_Size(0), m_Capacity(DEFAULT_CAPACITY), m_Storage(new T[m_Capacity])
	{}
	~List()
	{}
	bool append(T data)
	{
		if( (m_Size + 1) > m_Capacity)
		{
			this->resize(SCALING_FACTOR);
		}
		m_Storage[m_Size ++] = data;
		return true;
	}
	bool replace(int index, T data)
	{
		if(index > (int) m_Size || -index > (int) m_Size)
		{
			IndexException e("Index out of bounds.");
			throw e;
		}
		else
		{
			if (index < 0)
			{
				index = m_Size + index;
				m_Storage[index] = data;
			}
			else
			{
				m_Storage[index] = data;
			}
		}
		return true;
	}
	bool remove(int index)
	{
		if(index > (int) m_Size || -index > (int) m_Size)
		{
			IndexException e("Index out of bounds.");
			throw e;
		}
		else
		{
			if (index < 0)
			{
				index = m_Size + index;
				m_Storage[index] = NULL;
			}
			else
			{
				m_Storage[index] = NULL;
			}
		}
		m_Size --;

		if(m_Size < m_Capacity/(2*SCALING_FACTOR))
		{
			this->resize(-SCALING_FACTOR);
		}
		return true;
	}
	T operator [](int index) //get
	{
		T data;
		if(index > (int) m_Size || -index > (int) m_Size)
		{
			IndexException e("Index out of bounds.");
			throw e;
		}
		else
		{
			if(index < 0)
			{
				// start from end.
				index = m_Size + index;
				data = m_Storage[index];
			}
			else
			{
				data = m_Storage[index];
			}
		}
		return data;
	}
	unsigned int size(){return m_Size;}
	bool operator==(List& rhs)
	{
		if(m_Size != rhs.size())
		{
			return false;
		}
		else
		{
			for(int i = 0; i < m_Size; i++)
			{
				if(m_Storage[i] != rhs[i])
				{
					return false;
				}
			}
		}
		return true;
	}
	bool operator!=(List& rhs)
	{
		return !(*this == rhs);
	}
private:
	unsigned int m_Size, m_Capacity;
	static unsigned int DEFAULT_CAPACITY, SCALING_FACTOR;
	T* m_Storage;

	void resize(int scale)
	{
		if(scale > 0)
		{
			// increasing
			T* n_arr = new T[scale*m_Capacity];
			m_Capacity = scale*m_Capacity;
			for(int i = 0; i < m_Size; i++)
			{
				n_arr[i] = m_Storage[i];
			}
			m_Storage = n_arr;
		}
		else
		{
			//decreasing
			scale = -scale;
			int factor = m_Capacity/scale;
			T* n_arr = new T[factor];  //scale of -2 indicates halving the size (1/2)
			//printf("Scaling from %u to %u.\n", m_Capacity, factor);
			m_Capacity = factor;
			for(int i = 0; i < m_Size; i++)
			{
				n_arr[i] = m_Storage[i];
			}

			m_Storage = n_arr;
		}
	}



};
template <typename T>
unsigned int List<T>::DEFAULT_CAPACITY = 100;
template <typename T>
unsigned int List<T>::SCALING_FACTOR = 2;



#endif /* LIST_H_ */
