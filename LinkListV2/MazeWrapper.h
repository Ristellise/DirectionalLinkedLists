#pragma once
#include <string>
#include "CMaze.h"
#include <iostream>
class MazeWrapper
{
public:
    void DrawMap();
    MazeWrapper();
    MazeWrapper(std::string fpath);
    CNode* currentNode;
    CMaze Map;
    bool hasWon();
};

