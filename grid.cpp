#include <array>

// Header file
#include "grid.h"

/* Constructor for Grid class */
/* Creates a 10x10 grid */
Grid::Grid() : length(10), height(10)
{
    for(int row = 0; row<10; row++)
    {
        std::array<char,10> rowArray;
        for(int column = 0; column<10; column++)
        {
            rowArray[column] = ' ';
        }
        grid[row] = rowArray;
    }
}

/* Getter for @grid */
std::array<std::array<char,10>,10> Grid::getGrid() const
{
    return grid;
}

/* Setter for @grid */
void Grid::setGrid(std::array<std::array<char,10>,10> _grid)
{
    grid = _grid;
}

/* Allows a character to be changed in the @grid at a specified location */
void Grid::alterGridPositionChar(char character, int row, int col)
{
    grid[row][col] = character;
}