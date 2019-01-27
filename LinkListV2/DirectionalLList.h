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

class DirectionalNode
{
public:
    DirectionalNode* Node_UP = nullptr;
    DirectionalNode* Node_DOWN = nullptr;
    DirectionalNode* Node_LEFT = nullptr;
    DirectionalNode* Node_RIGHT = nullptr;
};

class DirectionalLList
{
public:
    int DrawOffSetX = 0;
    int DrawOffSetY = 0;
    DirectionalLList();
    DirectionalLList(std::string fpath);
    ~DirectionalLList();
    DirectionalNode* startNode = nullptr;
    DirectionalNode* endNode = nullptr;
};



class Maze
{
public:
    void DrawMap();
    Maze();
    Maze(std::string fpath);
    DirectionalNode* currentNode;
    DirectionalLList Map;
    
};