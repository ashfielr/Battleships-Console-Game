#ifndef GRID_H
#define GRID_H

#include <array> // Using std::array here

class Grid
{
    private:
        // The number of columns
        const int length;

        // The number of rows
        const int height;

        // The grid of characters
        // 2D Array in structure of an array of rows where each row is an array of the cell in the row 
        // [[Row1], [Row2], ... etc]
        std::array<std::array<char,10>,10> grid;
    
    public:
        /* Constructor */
        Grid();

        /* Getter for @grid */
        std::array<std::array<char,10>,10>  getGrid() const;

        /* Setter for @grid */
        void setGrid(std::array<std::array<char,10>,10> grid);
        
        /* Allows a character to be changed in the @grid at a specified location */
        void alterGridPositionChar(char character, int row, int col);
};
#endif