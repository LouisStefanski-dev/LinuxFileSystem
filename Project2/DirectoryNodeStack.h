#pragma once
#include "DirectoryNodeStackNode.h"

template<typename K>
class DirectoryNodeStack
{
private:
	DirectoryNodeStackNode<K>* top;
public:
	DirectoryNodeStack<K>() { top = nullptr; };
	//~DirectoryNodeStack<K>();
	void push(K* e);
	bool pop(K*& e);
	K* pop();
	bool empty() { return (top == nullptr); };
};

template<typename K>
inline K* DirectoryNodeStack<K>::pop()
{
	K* e = nullptr;
	if (top == NULL)
		return e;

	DirectoryNodeStackNode<K>* delNode = top;
	e = top->elem;
	top = top->next;
	delete delNode;

	return e;
}

template<typename K>
inline void DirectoryNodeStack<K>::push(K* e)
{
	DirectoryNodeStackNode<K>* newNode = new DirectoryNodeStackNode<K>();
	newNode->elem = e;
	newNode->next = top;
	top = newNode;
}

template<typename K>
inline bool DirectoryNodeStack<K>::pop(K*& e)
{
	if (top == NULL)
		return false;

	DirectoryNodeStackNode<K>* delNode = top;
	e = top->elem;
	top = top->next;
	delete delNode;

	return true;
}

//template<typename K>
//inline DirectoryNodeStack<K>::~DirectoryNodeStack()
//{
//	K* delNode;
//	while (!empty())
//	{
//		pop(delNode);
//	}
//}
