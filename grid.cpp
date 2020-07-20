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
        grid[row] = rowArray;
    }
}

/* Getter for @grid */
array<array<char,10>,10> Grid::getGrid() const
{
    return grid;
}

/* Setter for @grid */
void Grid::setGrid(array<array<char,10>,10> _grid)
{
    grid = _grid;
}