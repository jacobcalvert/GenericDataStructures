/**
 * @file   HashTable.h
 * @Author Jacob Calvert (jacob+info@jacobncalvert.com)
 * @date   October, 2014
 * @brief  Implementation of a hash table
 *
 * This hash table is a separate chaining type table. The predefined hash types for keys are
 * std::string
 * char *
 * int
 * long int
 * long long int
 *
 * If you want to use a key that is not supported, simply write a hashing function for that type
 * @see HashValue _hash(int & k)
 * @see HashValue _hash(char *str)
 */
#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include "GenericDefinitions.h"
#include <exception>
class GeneralHashTableException:public std::exception
{

public:
	GeneralHashTableException(std::string what):m_What(what)
	{

	}
	virtual ~GeneralHashTableException() throw()
	{
	}
	std::string m_What;
	virtual const char* what() const throw()
	{
		return m_What.c_str();
	}
};
template <typename K, typename V>
class HashTable
{
public:
	/**
	 * Constructs a HashTable
	 */
	HashTable():m_Size(0), m_ModCount(0)
	{
		/*
		 * initialize all the nodes as objects that are invalid
		 */
		m_Storage = new HashTableNode<K, V>[HASH_SIZE];

	}
	/**
	 * copy constructor
	 */
	HashTable(HashTable&rhs)
	{
		m_Size = rhs.m_Size;
		m_ModCount = rhs.m_ModCount;
		m_Storage = new HashTableNode<K, V>[HASH_SIZE];
		memcpy(m_Storage, rhs.m_Storage, sizeof(HashTableNode<K, V>)*HASH_SIZE);
	}
	/**
	 * assignment constructor
	 */
	HashTable & operator=(HashTable &rhs)
	{
		if(*this != rhs)
		{

			m_Size = rhs.m_Size;
			m_ModCount = rhs.m_ModCount;
			m_Storage = new HashTableNode<K, V>[HASH_SIZE];
			memcpy(m_Storage, rhs.m_Storage, sizeof(HashTableNode<K, V>)*HASH_SIZE);
		}

		return *this;
	}
	/**
	 * destructor
	 */
	~HashTable()
	{
		delete []m_Storage;
	}
	/**
	 * returns the number of elements in the table
	 */
	unsigned long long size(){return m_Size;}
	/**
	 * sets a value into the table corresponding to the key
	 * @param key the unique key
	 * @param val the value
	 */
	void set(K key, V val)
	{
		m_ModCount ++;
		bool key_exists = true;
		try
		{
			get(key);
		}
		catch (GeneralHashTableException &e)
		{
			key_exists = false;
		}
		if(key_exists)
		{
			update(key,val);
			return;
		}
		unsigned int hash_key = hash(key);
		HashTableNode<K, V> *p = &m_Storage[hash_key];
		if(p->valid)
		{
			//chain down
			while(p->next)
			{
				p = p->next;
			}
			p->next = new HashTableNode<K,V>;
			p->next->prev = p;
			p->next->valid=true;
			p->next->key = key;
			p->next->value = val;
		}
		else
		{
			HashTableNode<K, V> *p = &m_Storage[hash_key];
			p->valid = true;
			p->value = val;
			p->key = key;
		}
		m_Size++;
	}
	/**
	 * retrieves the value associated with the given key in the table
	 * throws an error if the key does not exist
	 * @param key the unique key
	 *
	 */
	V get(K key)
	{
		unsigned int hash_key = hash(key);
		HashTableNode<K, V> *p = &m_Storage[hash_key];
		if(p->valid)
		{
			if(p->key == key)
			{
				return p->value;
			}
			else
			{
				while(p->next)
				{
					if(p->next->key == key)
					{
						return p->next->value;
					}
					p = p->next;
				}
			}
		}
		GeneralHashTableException e("Key not found.");
		throw e;
	}
	/**
	 * removes the value associated with the given key
	 * @param key the unique key
	 * returns false if not found
	 */
	bool remove(K key)
	{

		if(!contains(key))
		{
			return false;
		}
		else
		{
			m_ModCount++;
			unsigned int hash_key = hash(key);
			HashTableNode<K, V> *p = &m_Storage[hash_key];
			if(p->valid)
			{

				if(p->key == key)
				{
					p->valid = false;
					if(p->next)m_Storage[hash_key] = *(p->next);
				}
				else
				{
					while(p->next)
					{
						if(p->next->key == key)
						{
							p->valid = false;
							p->prev->next = p->next;
							delete p;
							break;
						}
						p = p->next;
					}
				}
			}
			m_Size--;
			return true;
		}
	}
	/**
	 * checks if the given given key is in the hashtable
	 * @param key the unique key
	 * return true if found, false otherwise
	 */
	bool contains(K key)
	{
		bool key_exists = true;
		try
		{
			get(key);
		}
		catch (GeneralHashTableException &e)
		{
			key_exists = false;
		}
		return key_exists;
	}
	/**
	 * This proxy class is used to handle setting and getting
	 * values in the hashtable through the bracket operators.
	 *
	 */
	class proxy
	{
		HashTable<K, V> &h;
		K key;
	public:
		/**
		 * proxy constructor
		 */
		proxy(HashTable<K, V> &h, K key) : h(h), key(key) {}

		/**
		 * implicit converter for when we are getting a value
		 * with the bracket operator
		 */
		operator V() const
		{
			return h.get(key);
		}
		/**
		 * implicit converter for when we are getting a value
		 * with the bracket operator
		 */
		operator V()
		{
			return h.get(key);
		}
		/**
		 * += update operator
		 */
		proxy operator+=(V const &v)
		{
			V v_old = h.get(key);
			V v_new = v_old + v;
			h.set(key, v_new);
			return *this;
		}
		proxy operator++()
		{
			return *this;
		}


		/**
		 * converter to set the value given by the param
		 * @param value the value to set by proxy.key
		 *
		 */
		proxy &operator=(V const &value)
		{
			h.set(key, value);
			return *this;
		}
	};
	/**
	 * the proxy call for setting or getting a value by key
	 * via the proxy class
	 * @param k the unique key
	 * @see get(K key);
	 * @see set(K key, V val);
	 */
	proxy operator [] ( const K& k) { return proxy(*this, k); }
	/**
	 * get the modification count of the structure
	 */
	unsigned long long mod_count(){return m_ModCount;}
	/**
	 * iterator to go over the items in the table in a linear-like fashion
	 *
	 */
	class iterator
	{
	private:
		HashTableNode<K, V> *table;
		long long mods, loc;
		HashTable<K, V> &ht;
	public :
		/**
		 * Constructor
		 */
		iterator(HashTable<K, V> &h, long long start_at):mods(h.mod_count()),loc(start_at), ht(h)
		{
			table = new HashTableNode<K, V>[h.size()];
			long long k = 0;
			for(long long i = 0; i < HASH_SIZE; i++)
			{
				HashTableNode<K, V> *p = &(h.m_Storage[i]);
				while(p)
				{
					if(p->valid)
					{
						table[k++] = *p;
					}
					p=p->next;
				}
				if(k == h.size())break;
			}
		}
		/**
		 * moves the iterator to the next position
		 * @see next();
		 */
		iterator& operator ++(int)
		{
			loc++;
			return *this;
		}
		/**
		 * moves the iterator to the previous position
		 * @see prev();
		 */
		iterator& operator--(int)
		{
			loc--;
			return *this;
		}
		/**
		 * moves the iterator to the next position
		 * @see operator++();
		 */
		void next()
		{
			loc++;
		}
		/**
		 * moves the iterator to the previous position
		 * @see operator--();
		 */
		void prev()
		{
			loc--;
		}
		/**
		 * returns the linear position of the iterator in range [0, ht.size())
		 */
		long long pos()
		{
			return loc;
		}
		/**
		 * returns the last valid iterator position
		 */
		long long end()
		{
			return ht.size()-1;
		}
		/**
		 * returns the first valid iterator position
		 */
		long long begin()
		{
			return 0;
		}
		/**
		 * gets the key at the iterator's current position
		 */
		K key()
		{
			if(loc < ht.size() && loc >-1 && mods == ht.mod_count())
			{
				return table[loc].key;
			}
			else
			{
				GeneralHashTableException e("Iterator error.");
				throw e;
			}
		}
		/**
		 * gets the value at the iterator's current position
		 */
		V value()
		{
			if(loc < ht.size() && loc >-1 && mods == ht.mod_count())
			{
				return table[loc].value;
			}
			else
			{
				GeneralHashTableException e("Iterator error.");
				throw e;
			}
		}
	};
	/**
	 * returns an iterator set to begin at the beginning of the
	 * table
	 */
	iterator *begin()
	{
		return new iterator(*this, 0);
	}
	/**
	 * returns an iterator set to begin at the end of the table
	 */
	iterator *end()
	{
		return new iterator(*this, m_Size-1);
	}

private:
	static unsigned int HASH_SIZE;
	unsigned long long m_Size, m_ModCount;
	HashTableNode<K, V> *m_Storage;
	/**
	 * internally called hash function
	 * returns the hash by calling the externally defined hash function
	 * @param key the key being hashed
	 */
	static unsigned int hash(K key)
	{
		HashValue hash_result = _hash(key) % HASH_SIZE;
		return hash_result;
	}
	void update(K key, V val)
	{
		unsigned int hash_key = hash(key);
		HashTableNode<K, V> *p = &m_Storage[hash_key];
		if(p->valid)
		{
			while(p->key != key) p = p->next;
			p->value = val;
		}
	}

};
template <typename K, typename V>
unsigned int HashTable<K,V>::HASH_SIZE = HASH_TABLE_SIZE;


#endif /* HASHTABLE_H_ */
