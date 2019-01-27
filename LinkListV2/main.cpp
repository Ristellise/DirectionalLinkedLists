#include "DirectionalLList.h"
#include <string>
#include <iostream>
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#endif

/**
| Desc: returns the direction. or gives out a null hi
**/
Direction getSyncKeyState()
{
    // Bets not to bother with kbhit()
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
        if (d != Direction::D_NULL)
        {
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
            else
            {
                std::cout << std::endl << "Can't Get There From Here..." << std::endl;
                clearprint = false;
            }
            ddmap.DrawMap(); // Update map.
            if (clearprint)
            {
                std::cout << std::endl << "                            " << std::endl;
            }
            if (ddmap.hasWon())
            {
                std::cout << std::endl << "You win! To Play another Round, Relaunch the Maze App." << std::endl;
                return 0;
            }
        }
        
        
    }
    return 0;
}