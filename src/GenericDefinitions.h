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



#endif /* GENERICDEFINITIONS_H_ */
