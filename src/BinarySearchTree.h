/**
 * @file   BinarySearchTree.h
 * @Author Jacob Calvert (jacob+info@jacobncalvert.com)
 * @date   October, 2014
 * @brief  Implementation of a binary search tree
 *
 * This implemtation of the ADT BST is node based and provides many
 * common BST operations
 */

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_
#include "GenericDefinitions.h"
#include <exception>
class GeneralTreeException:public std::exception
{

public:
	GeneralTreeException(std::string what):m_What(what)
	{

	}
	virtual ~GeneralTreeException() throw()
	{

	}
	std::string m_What;
	virtual const char* what() const throw()
	{
		return m_What.c_str();
	}
};
template <typename T>
class BinarySearchTree
{
public:
	/**
	 * BinarySearchTree constructor
	 */
	BinarySearchTree():m_Root(0), m_Size(0),m_Indexer(0), m_PreOrder(0), m_InOrder(0), m_PostOrder(0)
	{}
	/**
	 * BinarySearchTree destructor
	 */
	~BinarySearchTree()
	{
	}
	/**
	 * inserts a value into the heap
	 * @param data the data being inserted
	 */
	void insert(T data)
	{
		if(m_Size == 0)
		{
			m_Root = new TreeNode<T>;
			m_Root->left = new TreeNode<T>;
			m_Root->right= new TreeNode<T>;
			m_Root->right->parent = m_Root;
			m_Root->left->parent = m_Root;
			m_Root->data = data;
			m_Root->parent = 0;
			m_Root->valid = true;
		}
		else
		{
			insert(data, m_Root);
		}
		m_Size++;
	}
	/**
	 * searches the heap for the specified value
	 * returns true if found, false otherwise
	 * @param data the data being searched for
	 */
	bool find(T data)
	{
		if(!m_Size)return false;
		else return find(data, m_Root);
	}
	/**
	 * NOT IMPL'D
	 */
	bool remove(T data)
	{
		TreeNode<T> * node = find_node(data);
		if(!node)return false;
		else return remove(node);
	}
	bool remove(TreeNode<T>*node)
	{
		GeneralTreeException e("Method not implemented.");
		throw e;
		if(node  && node->valid)
		{
			if(node->num_children() == 0)
			{
				node->valid = false; //esseintially just nullifying it
			}
			else if(node->num_children() == 1)
			{
				if(node->left->valid)//has only a left child
				{

					if(node->parent->left == node)
					{
						//we are left child
						node->parent->left = node->left;
					}
					else
					{
						node->parent->right = node->left;
					}
					node->left->parent = node->parent;
				}
				else
				{
					if(node->parent->left == node)
					{
						//we are left child
						node->parent->left = node->right;
					}
					else
					{
						node->parent->right = node->right;
					}
					node->right->parent = node->parent;
				}
			}
			else
			{
				TreeNode<T>* p = node->left;
				while(p->right->valid)
				{
					p = p->right;
				}
				node->data = p->data;
				remove(p);

			}
			m_Size--;
			return true;
		}
		else return false;
	}
	/**
	 * finds and returns the node with the specified data
	 * or 0 if it is not found
	 * @param data the data to find and get
	 */
	TreeNode<T> *find_node(T data)
	{
		if(!m_Size)
		{
			return 0;
		}
		TreeNode<T> * node = find_node(data, m_Root);
		if(!node)
		{
			return 0;
		}
		return node;
	}
	/**
	 * returns the size of the tree (number of nodes)
	 */
	long long size()
	{
		return m_Size;
	}
	/**
	 * NOT IMPL'D
	 */
	long long height()
	{
		GeneralTreeException e("Method not implemented.");
		throw e;
		return 0; //not impld yet
	}
	/**
	 * returns an array containing the preorder traversal of the tree
	 * or throws an exception if the tree is empty
	 */
	T *preorder()
	{
		if(!m_Size)
		{
			GeneralTreeException e("Cannot traverse an empty tree.");
			throw e;
		}
		m_PreOrder = new T[m_Size];
		m_Indexer = 0;
		preorder(m_Root);
		return m_PreOrder;

	}
	/**
	 * returns an array containing the inorder traversal of the tree
	 * or throws an exception if the tree is empty
	 */
	T *inorder()
	{
		if(!m_Size)
		{
			GeneralTreeException e("Cannot traverse an empty tree.");
			throw e;
		}
		m_InOrder = new T[m_Size];
		m_Indexer = 0;
		inorder(m_Root);
		return m_InOrder;

	}
	/**
	 * returns an array containing the postorder traversal of the tree
	 * or throws an exception if the tree is empty
	 */
	T *postorder()
	{
		if(!m_Size)
		{
			GeneralTreeException e("Cannot traverse an empty tree.");
			throw e;
		}
		m_PostOrder = new T[m_Size];
		m_Indexer = 0;
		postorder(m_Root);
		return m_PostOrder;

	}
private:
	TreeNode<T>* m_Root;
	long long m_Size, m_Indexer;
	T* m_PreOrder, *m_InOrder, *m_PostOrder;
	void preorder( TreeNode<T> * node)
	{
		if(!node->valid)return;

		m_PreOrder[m_Indexer++] = node->data;
		preorder(node->left);
		preorder(node->right);
	}
	void inorder( TreeNode<T> * node)
	{
		if(!node->valid)return;

		inorder(node->left);
		m_InOrder[m_Indexer++] = node->data;
		inorder(node->right);
	}
	void postorder( TreeNode<T> * node)
	{
		if(!node->valid)return;

		postorder(node->left);
		postorder(node->right);
		m_InOrder[m_Indexer++] = node->data;
	}
	bool find(T data, TreeNode<T> *node)
	{
		if(node->valid)
		{
			if(node->data == data)return true;
			else if(data < node->data)return find(data, node->left);
			else return find(data, node->right);
		}
		else
		{
			return false;
		}
	}
	TreeNode<T> * find_node(T data, TreeNode<T> *node)
	{
		if(node->valid)
		{
			if(node->data == data)return node;
			else if(data < node->data)return find_node(data, node->left);
			else return find_node(data, node->right);
		}
		else
		{
			return 0;
		}
	}
	void insert(T data, TreeNode<T>* node)
	{
		if(!node->valid)
		{
			node->left = new TreeNode<T>;
			node->right= new TreeNode<T>;
			node->right->parent = node;
			node->left->parent = node;
			node->data = data;
			node->valid = true;
		}
		else
		{
			if(data < node->data)
			{
				insert(data, node->left);
			}
			else
			{
				insert(data, node->right);
			}
		}
	}
};



#endif /* BINARYSEARCHTREE_H_ */
