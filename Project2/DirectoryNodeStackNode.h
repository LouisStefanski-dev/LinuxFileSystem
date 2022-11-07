#pragma once
#include "DirectoryNode.h"
template<typename K>
class DirectoryNodeStackNode
{
public:
	K* elem;
	DirectoryNodeStackNode* next;

	DirectoryNodeStackNode() { next = nullptr; elem = nullptr; };
};

