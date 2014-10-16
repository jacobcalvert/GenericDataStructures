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

#endif /* GENERICDEFINITIONS_H_ */
