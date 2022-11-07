#pragma once
#include "QueueNode.h"

template<typename K>
class Queue
{
public:
    QueueNode<K>* first;
    QueueNode<K>* last;
public:
    Queue<K>();

    void enqueue(K* e);
    bool empty() { return (first == nullptr); };
    bool dequeue(K*& e);
};

template<typename K>
inline Queue<K>::Queue()
{
    first = nullptr;
    last = nullptr;
}

template<typename K>
inline bool Queue<K>::dequeue(K*& e)
{
    if (empty())
        return false;

    e = first->elem;
    QueueNode<K>* delNode = first;
    first = first->next;
    if (first == nullptr)
        last = nullptr;
    delete delNode;

    return true;
}

template<typename K>
inline void Queue<K>::enqueue(K* e)
{
    QueueNode<K>* newNode = new QueueNode<K>();
    newNode->elem = e;
    if (last == nullptr)
    {
        first = newNode;
    }
    else
    {
        last->next = newNode;
    }
    last = newNode;
}
