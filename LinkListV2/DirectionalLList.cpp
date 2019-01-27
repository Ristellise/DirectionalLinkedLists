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
{
    std::cout << "No file path provided." << std::endl;
}

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
        
        while (std::getline(in,buff))
        {
            DirectionalNode* currentDNode = new DirectionalNode();
            if (this->startNode == nullptr)
            {
                this->startNode = new DirectionalNode();
                this->endNode = this->startNode;
            }
            NextNodeDirection = getDirectionfromString(buff[0]);
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
    }
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

void Maze::DrawMap()
{
    int drwx = negateIfLessThanZeroButMakeItZeroIfItIsMoreThanZero(this->Map.DrawOffSetX)*2;
    int drwy = negateIfLessThanZeroButMakeItZeroIfItIsMoreThanZero(this->Map.DrawOffSetY)*2+2;
    DirectionalNode* currentDNode = this->Map.startNode;
    Direction lastSide = Direction::D_NULL;
    while (true)
    {
        gotoxy(drwx, drwy);

        if (currentDNode == nullptr)
        {
            break;
        }

        if (lastSide != Direction::D_DOWN && currentDNode->Node_DOWN != nullptr)
        {
            OnNode(currentNode, currentDNode);
            drwy++;
            gotoxy(drwx, drwy);
            std::cout << "|";
            drwy++;
            gotoxy(drwx, drwy);
            lastSide = Direction::D_UP; // lastSide is always Relative to the nextNode.
            if (isTheEnd(currentDNode, this->Map.endNode)) { break; }
            else { currentDNode = currentDNode->Node_DOWN; }
        }
        else if (lastSide != Direction::D_UP && currentDNode->Node_UP != nullptr)
        {
            OnNode(currentNode, currentDNode);
            drwy--;
            gotoxy(drwx, drwy);
            std::cout << "|";
            drwy--;
            gotoxy(drwx, drwy);
            lastSide = Direction::D_DOWN; // lastSide is always Relative to the nextNode.
            if (isTheEnd(currentDNode, this->Map.endNode)) { break; }
            else { currentDNode = currentDNode->Node_DOWN; }
        }
        else if (lastSide != Direction::D_LEFT && currentDNode->Node_LEFT != nullptr)
        {
            OnNode(currentNode, currentDNode);
            drwx--;
            gotoxy(drwx, drwy);
            std::cout << "-";
            drwx--;
            gotoxy(drwx, drwy);
            lastSide = Direction::D_RIGHT; // lastSide is always Relative to the nextNode.
            if (isTheEnd(currentDNode, this->Map.endNode)) { break; }
            else { currentDNode = currentDNode->Node_DOWN; }
        }
        else if (lastSide != Direction::D_RIGHT && currentDNode->Node_RIGHT != nullptr)
        {
            OnNode(currentNode, currentDNode);
            drwx++;
            gotoxy(drwx, drwy);
            std::cout << "-";
            drwx++;
            gotoxy(drwx, drwy);
            lastSide = Direction::D_LEFT; // lastSide is always Relative to the nextNode.
            if (isTheEnd(currentDNode, this->Map.endNode)) { break; }
            else { currentDNode = currentDNode->Node_DOWN; }
        }
        else
        {
            OnNode(currentNode, currentDNode);
            if (currentDNode == this->Map.endNode)
            {
                break;
            }
            
        }

    }
    OnNode(currentNode, this->Map.endNode);
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