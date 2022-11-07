#pragma once
#include <string>
class DirectoryNode
{
public:
	DirectoryNode* sub, * last, * next, * prior;
	//DirectoryNode* first;
	DirectoryNode();
	std::string name;
};

