#pragma once
#include <string>

enum Direction
{
    D_UP,
    D_DOWN,
    D_LEFT,
    D_RIGHT,
    D_NULL,
    D_COUNT
};

class CNode
{
public:
    CNode* Node_UP = nullptr;
    CNode* Node_DOWN = nullptr;
    CNode* Node_LEFT = nullptr;
    CNode* Node_RIGHT = nullptr;
};

class CMaze
{
public:
    int DrawOffSetX = 0;
    int DrawOffSetY = 0;
    CMaze();
    CMaze(std::string fpath);
    ~CMaze();
    CNode* startNode = nullptr;
    CNode* endNode = nullptr;
};