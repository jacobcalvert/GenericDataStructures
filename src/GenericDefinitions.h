#ifndef GENERICDEFINITIONS_H_
#define GENERICDEFINITIONS_H_
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


#endif /* GENERICDEFINITIONS_H_ */
