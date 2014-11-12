/**
* @file   GenericDefinitions.h
 * @Author Jacob Calvert (jacob+info@jacobncalvert.com)
 * @date   September, 2014
 * @brief  Definitions of generically used items in the project
 *
 * This file contains several definitions of common structures such as linked list
 * nodes and tree nodes.
 */
#ifndef GENERICDEFINITIONS_H_
#define GENERICDEFINITIONS_H_
#include <string>
#define HASH_TABLE_SIZE 9973 /**< Prime for hashing. If you change this, make it a prime number N
								so that hashes are equally distributed in the range [0,N) */


enum RedBlackTreeNodeColor
{
	RedBlackTreeNodeColor_RED = 0,
	RedBlackTreeNodeColor_BLACK
};
template <typename T>
class Node
{
public:
	/**
	 * Node Constructor
	 */
	Node():next(0),prev(0){}
	~Node(){}
	T data;
	Node* next, *prev;
};
template <typename K,typename V>
class HashTableNode
{
public:
	HashTableNode():next(0), prev(0), valid(false)
	{}
	K key;
	V value;
	HashTableNode<K, V> * next, *prev;
	bool valid;
};
template <typename T>
class TreeNode
{
public:
	/**
	 * TreeNode constructor
	 */
	TreeNode():left(0), right(0), parent(0), valid(false)
	{}
	T data;
	TreeNode *left, *right, *parent;
	bool valid;
	int num_children()
	{
		int num = 0;
		if(left->valid)num++;
		if(right->valid)num++;
		return num;
	}
};
template <typename T>
class
RedBlackTreeNode
{
public:
	/**
	 * RedBlackTreeNode constructor
	 */
	RedBlackTreeNode():left(0),right(0),parent(0),valid(false),color(RedBlackTreeNodeColor_BLACK)
	{}

	RedBlackTreeNode *left, *right, *parent;
	T data;
	bool valid;
	RedBlackTreeNodeColor color;

};
typedef unsigned long long HashValue;///< typedef to make things clearer, HashValue may be a class in the future
/**
 * calculates the hashvalue of the given string
 * returns a HashValue
 * @param str the string being hashed
 * @see HashTable
 */
HashValue _hash(std::string & str)
{
	HashValue v = 0;
	for(unsigned long long i = 0; i < str.size(); i++)
	{
		v += str[i]*HASH_TABLE_SIZE;
	}
	v = v>>5;
	v+= HASH_TABLE_SIZE;
	return v;
}
/**
 * calculates the hashvalue of the given string
 * returns a HashValue
 * @param str the string being hashed
 * @see HashTable
 */
HashValue _hash(char* str)
{
	HashValue v = 0;
	while(*str)
	{
		v += *str;
		v+= HASH_TABLE_SIZE;
		str++;
	}
	v = v>>5;
	v+= HASH_TABLE_SIZE;
	return v;
}
/**
 * calculates the hashvalue of the given char
 * returns a HashValue
 * @param c the char being hashed
 * @see HashTable
 */
HashValue _hash(char c)
{
	HashValue v = 1;
	v*=c*HASH_TABLE_SIZE;
	v = v>>13;
	v*=3;
	v+= HASH_TABLE_SIZE;
	return v;
}
/**
 * calculates the hashvalue of the given integer
 * returns a HashValue
 * @param k the integer being hashed
 * @see HashTable
 */
HashValue _hash(long long int & k)
{
	HashValue v = 1;
	v*=k*HASH_TABLE_SIZE;
	v = v>>13;
	v*=3;
	v+= HASH_TABLE_SIZE;
	return v;
}
/**
 * calculates the hashvalue of the given integer
 * returns a HashValue
 * @param k the integer being hashed
 * @see HashTable
 */
HashValue _hash(long int & k)
{
	HashValue v = 1;
	v*=k*HASH_TABLE_SIZE;
	v = v>>11;
	v*=3;
	v+= HASH_TABLE_SIZE;
	return v;
}
/**
 * calculates the hashvalue of the given integer
 * returns a HashValue
 * @param k the integer being hashed
 * @see HashTable
 */
HashValue _hash(int & k)
{
	HashValue v = 1;
	v*=k*HASH_TABLE_SIZE;
	v = v>>3;
	v*=3;
	v+= HASH_TABLE_SIZE;
	return v;
}

#endif /* GENERICDEFINITIONS_H_ */
