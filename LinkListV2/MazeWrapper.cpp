#include "MazeWrapper.h"
#ifdef _WIN32
#include <conio.h>
#include <windows.h>

// Windows Function to set Cursor to A Spcific location on the terminal.
void gotoxy(int x, int y)
{
    // Casting int to a short. bad practise but in typical cases, should not be a big issue.
    COORD p = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

#else

// Lazy to do other methods.
void gotoxy(int x, int y)
{
    std::cout << "I'm lazy to do the other C++ ways :P" << std::endl;
}

#endif


/*----- MazeWrapper Class -----*/
// The meaning behind the method name is long gone but this function
// serves to to a simple test if the value is positive.
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

// Check if player Is on the Node, then we draw the X. Else we draw a O.
void OnNode(CNode* currentNode, CNode* currentDNode)
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

struct nextNodeResult
{
    Direction direction;
    CNode* Node;
    nextNodeResult(Direction direction, CNode* Node) { this->direction = direction; this->Node = Node; }
    nextNodeResult() {}
};

// gets the next direction and also prevent it from getting the previous node
// so that to stop it from pointing fingers at each other while drawing.
// https://i.imgur.com/1Spvblh.png
// [Illustrated image of what is to happen when they point at each other without any referance to the previous instance.]
nextNodeResult getNextNode(CNode* previousNode, CNode* currentNode)
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
        return nextNodeResult(Direction::D_NULL, nullptr);
    }
}

// Main DRawMap call. You can think of this as your Render() function.
void MazeWrapper::DrawMap()
{
    // Drawwing offsets. so that the map won't be half gone.
    int drwx = negateIfLessThanZeroButMakeItZeroIfItIsMoreThanZero(this->Map.DrawOffSetX) * 2;
    int drwy = negateIfLessThanZeroButMakeItZeroIfItIsMoreThanZero(this->Map.DrawOffSetY) * 2 + 2; // the + 2 is for the debug prints.
    CNode* currentDNode = this->Map.startNode;
    CNode* previousDNode = nullptr;
    nextNodeResult nextDNode;
    while (true)
    {
        gotoxy(drwx, drwy);

        if (currentDNode == nullptr)
        {
            break;
        }
        OnNode(currentNode, currentDNode); // Draw current Node
        nextDNode = getNextNode(previousDNode, currentDNode); // Get nextNode
        // if the nextNode is null, we stop.
        if (nextDNode.Node == nullptr)
        {
            break;
        }
        else
        {
            // Switch case for drawing the pipe.
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
    // We don't have a additional switch case like we do in DirectionalList Class
    // Since the missing node is handled there.

}

MazeWrapper::MazeWrapper()
{
    // Haha, YeS
    // Default Constructor... what else?
    std::cout << "NO U" << std::endl;
}

MazeWrapper::MazeWrapper(std::string fpath)
{
    // Constructor with map parsing.
    this->Map = CMaze(fpath);
    this->currentNode = this->Map.startNode;
}

bool MazeWrapper::hasWon()
{
    // to check if the player has won or not.
    return (this->Map.endNode == this->currentNode);
}