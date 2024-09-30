#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct Cell {
    Cell(int x, int y)
    {
        this->x = x;
        this->y = y;

        up = true;
        left = true;
    }

    int x, y;
    bool visited = false, up : 1, left : 1;
};

bool checkNeighbours(Cell* current, vector<Cell*>& neighbours, const vector<vector<Cell*>>& cellList, int rows, int cols)
{
    //Up
    if (current->y - 1 >= 0)
    {
        if (!cellList[current->y - 1][current->x]->visited)
        {
            neighbours.push_back(cellList[current->y - 1][current->x]);
        }
    }

    // Right
    if (current->x + 1 < cols)
    {
        if (!cellList[current->y][current->x + 1]->visited)
        {
            neighbours.push_back(cellList[current->y][current->x + 1]);
        }
    }

    //Down
    if (current->y + 1 < rows)
    {
        if (!cellList[current->y + 1][current->x]->visited)
        {
            neighbours.push_back(cellList[current->y + 1][current->x]);
        }
    }

    //Left
    if (current->x - 1 >= 0)
    {
        if (!cellList[current->y][current->x - 1]->visited)
        {
            neighbours.push_back(cellList[current->y][current->x - 1]);
        }
    }

    return !neighbours.empty();
}

int main()
{
    int cols, rows, seed;
    const int randLength = 100;
    int rand[randLength] =
    {72, 99, 56, 34, 43, 62, 31, 4,  70, 22, 6,  65, 96, 71, 29, 9,  98, 41, 90, 7,
     30, 3,  97, 49, 63, 88, 47, 82, 91, 54, 74, 2,  86, 14, 58, 35, 89, 11, 10, 60,
     28, 21, 52, 50, 55, 69, 76, 94, 23, 66, 15, 57, 44, 18, 67, 5,  24, 33, 77, 53,
     51, 59, 20, 42, 80, 61, 1,  0,  38, 64, 45, 92, 46, 79, 93, 95, 37, 40, 83, 13,
     12, 78, 75, 73, 84, 81, 8,  32, 27, 19, 87, 85, 16, 25, 17, 68, 26, 39, 48, 36};

    cin >> cols >> rows >> seed;

    //Fill the list with cells
    vector<vector<Cell*>> cellList(rows, vector<Cell*>(cols));
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            cellList[i][j] = new Cell(j, i);
        }
    }

    //Search
    stack<Cell*> stack;
    stack.push(cellList[0][0]);
    while (!stack.empty())
    {
        stack.top()->visited = true;

        //List of Neighbours
        vector<Cell*> neighbours;

        if (checkNeighbours(stack.top(), neighbours, cellList, rows, cols))
        {
            Cell* target = nullptr;
            if (neighbours.size() == 1)
            {
                target = neighbours.front();
            }
            else
            {
                target = neighbours[rand[seed] % neighbours.size()];
                seed++;
                if (seed >= randLength)
                {
                    seed = 0;
                }
            }

            if (target->y < stack.top()->y)
            {
                stack.top()->up = false;
            } 
            else if (target->x > stack.top()->x)
            {
                target->left = false;
            } 
            else if (target->y > stack.top()->y)
            {
                target->up = false;
            } 
            else if (target->x < stack.top()->x)
            {
                stack.top()->left = false;
            }

            stack.push(target);
        }
        else
        {
            stack.pop();
        }
    }

    //Building the Maze
    for (size_t i = 0; i < cols; i++)
    {
        // Maze Top
        if (cellList[0][i]->up) {
            cout << " " << "_";
        }
    }

    cout << "  " << endl;

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            //Rest of Maze
            if (cellList[i][j]->left)
            {
                cout << "|";
            }
            else
            {
                cout << " ";
            }

            if (i + 1 < rows)
            {
                if (cellList[i + 1][j]->up)
                {
                    cout << "_";
                }
                else
                {
                    cout << " ";
                }
            }
            else
            {
                cout << "_";
            }
        }

        //Last Wall
        cout << "| " << endl;
    }

    //Clean Up
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            delete cellList[i][j];
        }
    }
}


