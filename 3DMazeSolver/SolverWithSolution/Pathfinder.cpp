#include "Pathfinder.h"

Pathfinder::Pathfinder()
{
    for (int i = 0; i < MAZE_SIZE; ++i)
    {
        for (int j = 0; j < MAZE_SIZE; ++j)
        {
            for (int k = 0; k < MAZE_SIZE; ++k)
            {
                originalMaze[i][j][k] = 1;
            }
        }
    }
    srand(time(NULL));
}

string Pathfinder::toString() const
{
    ostringstream mazeAsString;
    
    for (int i = 0; i < MAZE_SIZE; ++i)
    {
        for (int j = 0; j < MAZE_SIZE; ++j)
        {
            for (int k = 0; k < MAZE_SIZE; ++k)
            {
                mazeAsString << originalMaze[i][j][k];
                if (k != (MAZE_SIZE -1)){
                     mazeAsString << " ";
                }
            }
            mazeAsString << endl;
        }
        if (i != (MAZE_SIZE -1))
        {
            mazeAsString << endl;
        }
    }
    
    return mazeAsString.str();
}


bool Pathfinder::importMaze(string fileName)
{
    validMaze = true;
    ifstream infile;
    int counter = 0;
    string currentMazePosition = "";
    int currentNum = -1;
    
    infile.open(fileName);
    
    if (!infile.is_open())
    {
        infile.close();
        validMaze = false;
        return false;
    }
    
    while (!infile.eof())
    {
        infile >> currentMazePosition;
        if (((counter == 0) || (counter == (std::pow(MAZE_SIZE, 3)))) && (currentMazePosition != "1"))
        {
            infile.close();
            while (mazeInfo.size() != 0)
            {
                mazeInfo.pop_front();
            }
            validMaze = false;
            return false;
        }
        if (currentMazePosition == "0")
        {
           mazeInfo.push_back(0);
           counter += 1;
        }
       
        else if (currentMazePosition == "1")
        {
            mazeInfo.push_back(1);
            counter += 1;
        }
       
        else 
        {
            infile.close();
            while (mazeInfo.size() != 0)
            {
                mazeInfo.pop_front();
            }
            validMaze = false;
            return false;
        }
    }
    
    if (counter != 125)
    {
        infile.close();
        while (mazeInfo.size() != 0)
        {
            mazeInfo.pop_front();
        }
        validMaze = false;
        return false;
    }
    
    if (mazeInfo.size() != 125)
    {
        infile.close();
        while (mazeInfo.size() != 0)
        {
            mazeInfo.pop_front();
        }
        validMaze = false;
        return false;
    }
    
    if (mazeInfo.front() != 1)
    {
        infile.close();
        while (mazeInfo.size() != 0)
        {
            mazeInfo.pop_front();
        }
        validMaze = false;
        return false;
    }
    
    if (mazeInfo.back() != 1)
    {
        infile.close();
        while (mazeInfo.size() != 0)
        {
            mazeInfo.pop_front();
        }
        validMaze = false;
        return false;
    }
    
    if (validMaze)
    {
        for (int i = 0; i < MAZE_SIZE; ++i)
        {
            for (int j = 0; j < MAZE_SIZE; ++j)
            {
                for (int k = 0; k < MAZE_SIZE; ++k)
                {
                    currentNum = mazeInfo.front();
                    mazeInfo.pop_front();
                    originalMaze[i][j][k] = currentNum;
                }
            }
        }
    }
    while (mazeInfo.size() != 0)
    {
        mazeInfo.pop_front();
    }
    
    infile.close();
    return true;
}


bool Pathfinder::findpath(int x, int y, int z)
{
    string positionAsString;
    positionAsString = + "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")";
    pathToExit.push_back(positionAsString);
    
    if (((x < 0) || (x >= MAZE_SIZE) || (y < 0) || (y >= MAZE_SIZE) || (z < 0) || (z >= MAZE_SIZE)) || (modfiedMaze[z][y][x] == 0) || (modfiedMaze[z][y][x] == 2)) 
    {
        pathToExit.pop_back();
        return false;
    }
    
    modfiedMaze[z][y][x] = 2;
    
    if ((x == 4) && (y == 4) && (z == 4))
    {
        return true;
    }
    
    if ((this->findpath((x - 1), y, z)) || (this->findpath((x + 1), y, z)) || (this->findpath(x, (y - 1), z)) || (this->findpath(x, (y + 1), z)) || (this->findpath(x, y, (z - 1))) || (this->findpath(x, y, (z + 1))))
    {
        return true;
    }
    else
    {
        pathToExit.pop_back();
        return false;
    }
}


vector<string> Pathfinder::solveMaze()
{
    for (int i = 0; i < MAZE_SIZE; ++i)
    {
        for (int j = 0; j < MAZE_SIZE; ++j)
        {
            for (int k = 0; k < MAZE_SIZE; ++k)
            {
                modfiedMaze[i][j][k] = originalMaze[i][j][k];
            }
        }
    }
    
    while(pathToExit.size() != 0)
    {
        pathToExit.pop_back();
    }
    
    
    if (findpath(0, 0, 0))
    {
        return pathToExit;
    }
    else
    {
        while(pathToExit.size() != 0)
        {
            pathToExit.pop_back();
        }
        return pathToExit;
    }
}


void Pathfinder::createRandomMaze()
{
    for (int i = 0; i < MAZE_SIZE; ++i)
    {
        for (int j = 0; j < MAZE_SIZE; ++j)
        {
            for (int k = 0; k < MAZE_SIZE; ++k)
            {
                originalMaze[i][j][k] = rand() % 2;
            }
        }
    }
    originalMaze[0][0][0] = 1;
    originalMaze[4][4][4] = 1;
}
