#pragma once
#include <string>
enum LLType
{
    LL_NULL,
    LL_UINT,
    LL_INT,
    LL_STRING,
    LL_UNKNOWN,
    LL_CHICKEN,
    LL_COUNT
};

class Node
{
public:
    Node* Next;
    LLType NodeType = LL_NULL;
};

class UIntNode : public Node
{
public:
    unsigned int data;
    LLType NodeType = LL_UINT;
};

class StringNode : public Node
{
public:
    std::string data;
    LLType NodeType = LL_STRING;
};

class IntNode : public Node
{
public:
    int data;
    LLType NodeType = LL_INT;
};

enum ChickenType
{
    CT_WHITE,
    CT_ROASTED
};

class Order
{
public:
    ChickenType chickenType;
    bool needsEgg;
};

class Customer
{
public:
    std::string name;
    Order CustOrder;
};



class ChickenRiceNode : public Node
{
public:
    Customer customer;
    LLType NodeType = LL_CHICKEN;
};