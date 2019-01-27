#include "DirectionalLList.h"
#include <iostream>
#include <fstream>
#ifdef _WIN32
#include <conio.h>
#include <windows.h>

void gotoxy(int x, int y)
{
    COORD p = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

#else

void gotoxy(int x, int y)
{
    std::cout << "I'm lazy to do the other C++ ways :P" << std::endl;
}

#endif

/*----- Directional LList Class -----*/

DirectionalLList::DirectionalLList()
{}

Direction getDirectionfromString(char i)
{
    switch (i)
    {
        case 'U':
        {
            return D_UP;
        }
        case 'D':
        {
            return D_DOWN;
        }
        case 'L':
        {
            return D_LEFT;
        }
        case 'R':
        {
            return D_RIGHT;
        }
    }
}

DirectionalLList::DirectionalLList(std::string fpath)
{
    std::cout << "Loading from:" << fpath.c_str() << std::endl;
    std::ifstream in(fpath);
    std::string buff("");
    Direction NextNodeDirection = D_COUNT;
    if (in.is_open())
    {
        DirectionalNode* currentDNode;
        while (std::getline(in,buff))
        {
            currentDNode = new DirectionalNode();
            
            if (this->startNode == nullptr)
            {
                this->startNode = new DirectionalNode();
                this->endNode = this->startNode;
            }
            else
            {
                switch (NextNodeDirection)
                {
                    case D_UP:
                    {
                        this->DrawOffSetY++;
                        this->endNode->Node_UP = currentDNode;
                        currentDNode->Node_DOWN = this->endNode;
                        this->endNode = currentDNode;
                        break;
                    }
                    case D_DOWN:
                    {
                        this->DrawOffSetY--;
                        this->endNode->Node_DOWN = currentDNode;
                        currentDNode->Node_UP = this->endNode;
                        this->endNode = currentDNode;
                        break;
                    }
                    case D_LEFT:
                    {
                        this->DrawOffSetX++;
                        this->endNode->Node_LEFT = currentDNode;
                        currentDNode->Node_RIGHT = this->endNode;
                        this->endNode = currentDNode;
                        break;
                    }
                    case D_RIGHT:
                    {
                        this->DrawOffSetX--;
                        this->endNode->Node_RIGHT = currentDNode;
                        currentDNode->Node_LEFT = this->endNode;
                        this->endNode = currentDNode;
                        break;
                    }
                    default:
                        break;
                }
            }
            NextNodeDirection = getDirectionfromString(buff[0]);
        }
        currentDNode = new DirectionalNode();
        switch (NextNodeDirection)
        {
        case D_UP:
        {
            this->DrawOffSetY++;
            this->endNode->Node_UP = currentDNode;
            currentDNode->Node_DOWN = this->endNode;
            this->endNode = currentDNode;
            break;
        }
        case D_DOWN:
        {
            this->DrawOffSetY--;
            this->endNode->Node_DOWN = currentDNode;
            currentDNode->Node_UP = this->endNode;
            this->endNode = currentDNode;
            break;
        }
        case D_LEFT:
        {
            this->DrawOffSetX++;
            this->endNode->Node_LEFT = currentDNode;
            currentDNode->Node_RIGHT = this->endNode;
            this->endNode = currentDNode;
            break;
        }
        case D_RIGHT:
        {
            this->DrawOffSetX--;
            this->endNode->Node_RIGHT = currentDNode;
            currentDNode->Node_LEFT = this->endNode;
            this->endNode = currentDNode;
            break;
        }
        default:
            break;
        }
    }
    std::cout << "Load OK!" << std::endl;
}


DirectionalLList::~DirectionalLList()
{
}


/*----- Maze Class -----*/
int negateIfLessThanZeroButMakeItZeroIfItIsMoreThanZero(int value)
{
    if (value > 0)
    {
        return value;
    }
    else
    {
        return 0;
    }
}

bool isTheEnd(DirectionalNode* Node, DirectionalNode* EndNode)
{
    if (Node == EndNode)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void OnNode(DirectionalNode* currentNode, DirectionalNode* currentDNode)
{
    if (currentNode == currentDNode)
    {
        std::cout << "X";
    }
    else
    {
        std::cout << "O";
    }
}



nextNodeResult getNextNode(DirectionalNode* previousNode, DirectionalNode* currentNode)
{
    if (currentNode->Node_DOWN != nullptr && currentNode->Node_DOWN != previousNode)
    {
        return nextNodeResult(Direction::D_DOWN, currentNode->Node_DOWN);
    }
    else if (currentNode->Node_LEFT != nullptr && currentNode->Node_LEFT != previousNode)
    {
        return nextNodeResult(Direction::D_LEFT, currentNode->Node_LEFT);
    }
    else if (currentNode->Node_RIGHT != nullptr && currentNode->Node_RIGHT != previousNode)
    {
        return nextNodeResult(Direction::D_RIGHT, currentNode->Node_RIGHT);
    }
    else if (currentNode->Node_UP != nullptr && currentNode->Node_UP != previousNode)
    {
        return nextNodeResult(Direction::D_UP, currentNode->Node_UP);
    }
    else
    {
        return nextNodeResult(Direction::D_NULL,nullptr);
    }
}

Direction getPreviousDirect(DirectionalNode* Node)
{
    if (Node->Node_DOWN != nullptr)
    {
        return Direction::D_DOWN;
    }
    else if (Node->Node_LEFT != nullptr)
    {
        return Direction::D_LEFT;
    }
    else if (Node->Node_RIGHT != nullptr)
    {
        return Direction::D_RIGHT;
    }
    else if (Node->Node_UP != nullptr)
    {
        return Direction::D_UP;
    }
    else
    {
        return Direction::D_NULL;
    }
}

void Maze::DrawMap()
{
    int drwx = negateIfLessThanZeroButMakeItZeroIfItIsMoreThanZero(this->Map.DrawOffSetX)*2;
    int drwy = negateIfLessThanZeroButMakeItZeroIfItIsMoreThanZero(this->Map.DrawOffSetY)*2+2;
    DirectionalNode* currentDNode = this->Map.startNode;
    DirectionalNode* previousDNode = nullptr;
    nextNodeResult nextDNode;
    while (true)
    {
        gotoxy(drwx, drwy);

        if (currentDNode == nullptr)
        {
            break;
        }
        OnNode(currentNode, currentDNode); // Draw current Node
        nextDNode = getNextNode(previousDNode,currentDNode);
        if (nextDNode.Node == nullptr)
        {
            break;
        }
        else
        {
            switch (nextDNode.direction)
            {
                case Direction::D_UP:
                {
                    drwy--;
                    gotoxy(drwx, drwy);
                    std::cout << "|";
                    drwy--;
                    gotoxy(drwx, drwy);
                    break;
                }
                case Direction::D_DOWN:
                {
                    drwy++;
                    gotoxy(drwx, drwy);
                    std::cout << "|";
                    drwy++;
                    gotoxy(drwx, drwy);
                    break;
                }
                case Direction::D_LEFT:
                {
                    drwx--;
                    gotoxy(drwx, drwy);
                    std::cout << "-";
                    drwx--;
                    gotoxy(drwx, drwy);
                    break;
                }
                case Direction::D_RIGHT:
                {
                    drwx++;
                    gotoxy(drwx, drwy);
                    std::cout << "-";
                    drwx++;
                    gotoxy(drwx, drwy);
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
        previousDNode = currentDNode;
        currentDNode = nextDNode.Node;
    }
    

}

Maze::Maze()
{
    std::cout << "NO U" << std::endl;
}

Maze::Maze(std::string fpath)
{
    this->Map = DirectionalLList(fpath);
    this->currentNode = this->Map.startNode;
}

bool Maze::hasWon()
{
    return (this->Map.endNode == this->currentNode);
}
