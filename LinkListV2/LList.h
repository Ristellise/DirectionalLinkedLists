#pragma once
#include "Listcontainers.h"
class LList
{
public:
    LList();
    ~LList();

    Node* LastNode;
    Node* FirstNode;
    Node* operator[] (size_t index); // TODO
    unsigned int nodesize = 0;
    bool appendNode(Node* type);
    bool removeNode(size_t index);
    bool insertNode(size_t index, Node* type);
};