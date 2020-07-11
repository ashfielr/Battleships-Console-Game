#include <array>
#include <memory>

// Header file
#include "grid.h"

using namespace std;

/* Constructor for Grid class */
Grid::Grid() : length(10), height(10)
{
    for(int row = 0; row<10; row++)
    {
        array<char,10> rowArray;
        for(int column = 0; column<10; column++)
        {
            rowArray[column] = ' ';
        }
        shared_ptr<array<char,10>> rowArrayPtr= make_shared<array<char,10>>();
        grid[row] = rowArrayPtr;
    }
}

/* Getter for @grid */
array<shared_ptr<array<char,10>>,10> Grid::getGrid()
{
    return grid;
}

/* Setter for @grid */
void Grid::setGrid(array<shared_ptr<array<char,10>>,10> _grid)
{
    grid = _grid;
}