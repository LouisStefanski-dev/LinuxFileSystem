#pragma once
#include <string>
#include "stringTreeNode.h"
#include "DirectoryNodeStack.h"

class StringTree
{
private:
    StringTreeNode* root, * curr;
    DirectoryNodeStack<StringTreeNode> treeStack;

    void add(std::string e, StringTreeNode*& thisRoot);
    bool search(std::string e, StringTreeNode*& thisRoot);
    void slideLeft();
    void deleteNode(StringTreeNode*& node);


public:
    StringTree() { root = NULL; curr = NULL; };
    ~StringTree() { deleteNode(root); };

    void add(std::string e) { add(e, root); };
    bool search(std::string e) { return search(e, root); };
    void gotoFirst();
    void gotoNext();
    bool atEnd() { return (curr == NULL); };
    bool getCurr(std::string& e);
};


