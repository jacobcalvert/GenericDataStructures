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
	T& operator [](int index)
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
			T* n_arr = new T[m_Capacity * (1/(-scale))];  //scale of -2 indicates halving the size (1/2)
			m_Capacity = m_Capacity * (1/(-scale));
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
