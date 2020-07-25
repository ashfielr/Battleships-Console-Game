#ifndef GRID_H
#define GRID_H

#include <array>
#include <memory>

class Grid
{
    private:
        // The number of columns
        int length;

        // The number of rows
        int height;

        // The grid of characters
        // 2D Array in structure of an array of rows where each row is an array of the cell in the row 
        // [[Row1], [Row2], etc]
        std::array<std::array<char,10>,10> grid;
    
    public:
        Grid();

        /* Getter for @grid */
        std::array<std::array<char,10>,10>  getGrid() const;

        /* Setter for @grid */
        void setGrid(std::array<std::array<char,10>,10> grid);
        
        /* Allows a character to be changed in the @grid */
        void alterGridPositionChar(char character, int row, int col);
};
#endif