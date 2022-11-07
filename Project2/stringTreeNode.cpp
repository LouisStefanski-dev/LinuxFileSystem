#include "stringTreeNode.h"

StringTreeNode::StringTreeNode()
{
    left = NULL;
    right = NULL;
}

StringTreeNode::StringTreeNode(std::string e)
{
    left = NULL;
    right = NULL;
    elem = e;
}