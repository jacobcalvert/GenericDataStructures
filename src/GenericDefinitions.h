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
	Node():next(0),prev(0){}
	~Node(){}
	T data;
	Node* next, *prev;
};
template <typename T>
class TreeNode
{
public:
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
	RedBlackTreeNode():left(0),right(0),parent(0),valid(false),color(RedBlackTreeNodeColor_BLACK)
	{}

	RedBlackTreeNode *left, *right, *parent;
	T data;
	bool valid;
	RedBlackTreeNodeColor color;

};

#endif /* GENERICDEFINITIONS_H_ */
