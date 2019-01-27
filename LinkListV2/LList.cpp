#include "LList.h"
#include <iostream>

LList::LList()
{
}

LList::~LList()
{
}

Node* traverse(Node* FirstNode, unsigned int index)
{
    Node* current = FirstNode;
    if (FirstNode == NULL)
    {
        return nullptr;
    }
    while (index != 0 && index > 0)
    {
        if (current->Next == nullptr)
        {
            return nullptr;
        }
        else
        {
            current = current->Next;
            index--;
        }
    }
    return current;
}

Node * LList::operator[](size_t index)
{
    return traverse(this->FirstNode, index);
}

bool LList::appendNode(Node * type)
{
    if (this->FirstNode == nullptr)
    {
        
        this->FirstNode = type;
        this->LastNode = type;
        std::cout << "Initalized First and Last Nodes" << std::endl;
        printf("Address of FirstNode is %p\n", (void *)this->FirstNode);
        printf("Address of LastNode is %p\n", (void *)this->LastNode);
        this->nodesize++;
    }
    else
    {
        if (this->LastNode != nullptr)
        {
            printf("Older LastNode is %p\n", (void *)this->LastNode);
            // We set the lastnode's next node address.
            this->LastNode->Next = type;
            // Update lastnode to point at the new last node.
            this->LastNode = type;
            printf("Updated LastNode is %p\n", (void *)this->LastNode);
            this->nodesize++;
        }
        else // Catching all cases.
        {
            printf("Rebuilding LastNode. This should not happen!\n");
            // get the firstnode
            Node* current = this->FirstNode;
            // Traverse till we find an end.
            while (true)
            {
                if (current == nullptr)
                {
                    // Found it!
                    this->LastNode = current;
                    current->Next = type;
                    this->nodesize++;
                    return true;
                }
                else
                {
                    current = current->Next;
                }
            }
        }
    }
    return true;
}

bool LList::removeNode(size_t index)
{
    Node* current = this->FirstNode;
    Node* previous = this->FirstNode;
    if (FirstNode == NULL)
    {
        throw std::exception("BOI");
    }
    while (index != 0 && index > 0)
    {
        if (current->Next == nullptr)
        {
            throw std::exception("BOI");
        }
        else
        {
            previous = current;
            current = current->Next;
            index--;
        }
    }
    previous->Next = current->Next;
    delete current; // begon thot
    return true;
}

bool LList::insertNode(size_t index, Node * type)
{
    Node* current = traverse(this->FirstNode, index);
    type->Next = current->Next;
    current->Next = type;
    return true;
}
