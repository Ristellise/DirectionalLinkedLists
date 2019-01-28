#pragma once
#include <string>
#include "CNode.h"
enum Direction
{
    D_UP,
    D_DOWN,
    D_LEFT,
    D_RIGHT,
    D_NULL,
    D_COUNT
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