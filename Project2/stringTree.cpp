#include "stringTree.h"

void StringTree::add(std::string e, StringTreeNode*& thisRoot)
{
    if (thisRoot == NULL)
    {

        thisRoot = new StringTreeNode(e);
        return;
    }

    if (e < thisRoot->elem)
    {
        add(e, thisRoot->left);
    }
    else
    {
        add(e, thisRoot->right);
    }
}


bool StringTree::search(std::string e, StringTreeNode*& thisRoot)
{
    if (thisRoot == NULL)
        return false;
    if (e == thisRoot->elem)
        return true;
    if (e < thisRoot->elem)
    {
        return search(e, thisRoot->left);
    }
    else
    {
        return search(e, thisRoot->right);
    }
}


void StringTree::slideLeft()
{
    if (curr->left != NULL)
    {
        treeStack.push(curr);
        curr = curr->left;
        slideLeft();
    }
}


void StringTree::gotoFirst()
{
    curr = root;
    slideLeft();
}


void StringTree::gotoNext()
{
    if (curr == NULL)
        return;

    if (curr->right != NULL)
    {
        curr = curr->right;
        slideLeft();
        return;
    }

    if (treeStack.pop(curr))
        return;

    curr = NULL;
    return;
}


bool StringTree::getCurr(std::string& e)
{
    if (atEnd())
        return false;

    e = curr->elem;
    return true;
}


void StringTree::deleteNode(StringTreeNode*& node)
{
    if (node == NULL)
        return;

    deleteNode(node->left);
    deleteNode(node->right);

    delete node;
}
