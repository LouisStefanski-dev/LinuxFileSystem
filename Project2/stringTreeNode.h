#pragma once
#include <string>

class StringTreeNode
{
public:
    std::string elem;
    StringTreeNode* left, * right;

    StringTreeNode();
    StringTreeNode(std::string e);
};

