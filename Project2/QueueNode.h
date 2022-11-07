#pragma once
template<typename K>
class QueueNode
{
public:
    K* elem;
    QueueNode<K>* next;

    QueueNode<K>() { next = nullptr; };
};

