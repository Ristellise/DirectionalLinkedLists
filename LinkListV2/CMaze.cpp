#include "CMaze.h"
#include <fstream>
#include <iostream>

/*----- Directional LList Class -----*/

// Empty Constructor. Nothing much.
CMaze::CMaze() {}

// Gets Direction Enum from a char.
Direction getDirectionfromString(char i)
{
    switch (i)
    {
        case 'U':
        {
            return Direction::D_UP;
        }
        case 'D':
        {
            return Direction::D_DOWN;
        }
        case 'L':
        {
            return Direction::D_LEFT;
        }
        case 'R':
        {
            return Direction::D_RIGHT;
        }
        default:
        {
            return Direction::D_NULL;
        }
    }
}

// The constructor with map loading.
CMaze::CMaze(std::string fpath)
{
    std::cout << "Loading from:" << fpath.c_str() << std::endl;
    std::ifstream in(fpath);
    std::string buff("");
    Direction NextNodeDirection = D_COUNT;
    if (in.is_open())
    {
        CNode* currentDNode;
        while (std::getline(in,buff))
        {
            
            
            // This handles the first node... 
            if (this->startNode == nullptr)
            {
                this->startNode = new CNode();
                this->endNode = this->startNode;
            }
            else
            {
                // Create new Node.
                currentDNode = new CNode();
                // check the Previous Direction Instructions on hwere to place this node.
                switch (NextNodeDirection)
                {
                    // lot of this is copy pasted. I could have trim it to lesser code but
                    // this should be good eough for now.
                    // I'll comment the first block and the rest should follow the same.
                    case D_UP:
                    {
                        // Increment DrawOffset
                        this->DrawOffSetY++;
                        // set the end node to the new DNode.
                        this->endNode->Node_UP = currentDNode;
                        // set the previous node to point ot the new Node.
                        currentDNode->Node_DOWN = this->endNode;
                        // move up the end node.
                        this->endNode = currentDNode;
                        // break because We want to finish up the case.
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
        // After the while loop is finished. It leaves 1 last node Unfilled.
        // I could do a | do{} while {blah} | but I prefer | while (blah) {do something} |.

        // Soo we create a New directionalNode.
        currentDNode = new CNode();
        // Same switch case. you know the drill.
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
    // Log print becase why not.
    std::cout << "Load OK!" << std::endl;
}


CMaze::~CMaze()
{
}
