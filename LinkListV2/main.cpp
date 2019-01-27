#include "DirectionalLList.h"
#include <string>
#include <iostream>
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#endif

/**
| Desc: Waits for a key to be pressed
|       and returns the direction.
**/
Direction getSyncKeyState()
{
    while (!_kbhit()) {}
    Sleep(200);
    if (GetAsyncKeyState(VK_UP))
    {
        return Direction::D_UP;
    }
    else if (GetAsyncKeyState(VK_DOWN))
    {
        return Direction::D_DOWN;
    }
    else if (GetAsyncKeyState(VK_LEFT))
    {
        return Direction::D_LEFT;
    }
    else if (GetAsyncKeyState(VK_RIGHT))
    {
        return Direction::D_RIGHT;
    }
    else
    {
        return Direction::D_NULL;
    }
}

int main()
{
    Maze ddmap("map.txt");

    Direction d = Direction::D_NULL;
    ddmap.DrawMap();
    bool clearprint = false;
    while (true)
    {
        clearprint = true;
        d = getSyncKeyState();
        if (d == Direction::D_DOWN && ddmap.currentNode->Node_DOWN != nullptr)
        {
            ddmap.currentNode = ddmap.currentNode->Node_DOWN;
        }
        else if (d == Direction::D_LEFT && ddmap.currentNode->Node_LEFT != nullptr)
        {
            ddmap.currentNode = ddmap.currentNode->Node_LEFT;
        }
        else if (d == Direction::D_RIGHT && ddmap.currentNode->Node_RIGHT != nullptr)
        {
            ddmap.currentNode = ddmap.currentNode->Node_RIGHT;
        }
        else if (d == Direction::D_UP && ddmap.currentNode->Node_UP != nullptr)
        {
            ddmap.currentNode = ddmap.currentNode->Node_UP;
            
        }
        else if (d == Direction::D_NULL)
        {
            //std::cout << "Invalid button" << std::endl;
        }
        else
        {
            std::cout << std::endl << "Can't Get There From Here..." << std::endl;
            clearprint = false;
        }

        if (d != Direction::D_NULL)
        {
            ddmap.DrawMap(); // Update map.
        }

        
    }
}