#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <list>
#include <cmath>
#include "PathfinderInterface.h"


class Pathfinder: public PathfinderInterface
{
    public:
        Pathfinder();
        string toString() const;
        void createRandomMaze();
        bool importMaze(string fileName);
        virtual vector<string> solveMaze();
        bool findpath(int x, int y, int z);
        
    private:
        const int MAZE_SIZE = 5;
        
        int originalMaze[5][5][5];
        int modfiedMaze[5][5][5];//Will have a 2 on a visited position
        
        bool validMaze = true;
        list<int> mazeInfo;//Contains the full maze as ones and zeros
        vector<string> pathToExit;
};