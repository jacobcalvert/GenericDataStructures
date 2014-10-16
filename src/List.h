/**
 * @file   List.h
 * @Author Jacob Calvert (jacob+info@jacobncalvert.com)
 * @date   September, 2014
 * @brief  Implementation of a dynamically sized array based list
 *
 * This implementation of the ADT List is based on a dynamically sized array.
 * The backend storage is resized on insert and remove operations when the size of
 * the list is below or above a certain threshold set by the static class variable
 * SCALING_FACTOR. The SCALING_FACTOR is set by default to 2. This means that the
 * the array will double in size when it gets more than halfway full and will half
 * its size when items are removed down to 1/4 the capacity.
 *
 * This can guarantee an amortized constant time analysis.
 */
#ifndef LIST_H_
#define LIST_H_
#include <exception>
#include <string>
class IndexException:public std::exception
{

public:
	IndexException(std::string what):m_What(what)
	{

	}
	virtual ~IndexException() throw()
	{

	}
	std::string m_What;
	virtual const char* what() const throw()
	{
		return m_What.c_str();
	}
};
template <typename T>
class List
{
public:
	/**
	 * List constructor.
	 */
	List():m_Size(0), m_Capacity(DEFAULT_CAPACITY), m_Storage(new T[m_Capacity])
	{}
	/*
	 * List destructor.
	 */
	~List()
	{
		delete[] m_Storage;
	}
	/**
	 * adds a value to the end of the list
	 *
	 * this method will add the value to the end of the list
	 * it may cause a resize operation
	 * @param data the value being added
	 */
	bool append(T data)
	{
		if( (m_Size + 1) > m_Capacity)
		{
			this->resize(SCALING_FACTOR);
		}
		m_Storage[m_Size ++] = data;
		return true;
	}
	/**
	 * replaces a value at specified index with another value
	 * will throw an exception if the index is out of bounds
	 *
	 * @param index the index at which the replace is performed
	 * @param data the value to replace the value at the spedcified index
	 */
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
	/**
	 * returns the index of the FIRST occurrence of the
	 * value specified in the parameter
	 * returns -1 if the value is not found
	 *
	 * @param data the value to be searched for
	 */
	int index_of(T data)
	{
		for(long long i = 0; i < m_Size; i++)
		{
			if(m_Storage[i] == data)
			{
				return i;
			}
		}
		return -1;
	}
	/**
	 * removes the FIRST occurrence of the value
	 * returns true if success, false otherwise
	 * @param data the value being removed
	 * @see remove_at(int index)
	 */
	bool remove(T data)
	{
		int index = index_of(data);
		if(index == -1)return false;//not found
		else return remove_at(index);
	}
	/**
	 * removes the data at the specified index
	 * throws an exception if the index doesn't exist
	 * @param index the index
	 */
	bool remove_at(int index)
	{
		if(index > (int) m_Size || -index > (int) m_Size)
		{
			IndexException e("Index out of bounds.");
			throw e;
		}
		else
		{
			if(index < 0) index = m_Size + index;
		}
		for(long long i = index; i < m_Size-1; i++)
		{
			m_Storage[i] = m_Storage[i+1]; //move things down.
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
	/**
	 * returns the size of the list
	 */
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
	/**
	 * checks if the value specified is in the list
	 * @param data the value being searched for
	 */
	bool contains(T data)
	{
		for(int i = 0; i < m_Size; i ++)
		{
			if(m_Storage[i] == data)
			{
				return true;
			}
		}
		return false;
	}
private:
	unsigned long long m_Size, m_Capacity;
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
