#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <array>
using namespace std;

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
        array<shared_ptr<array<char,10>>,10> grid;
    
    public:
        Grid();

        /* Getter for @grid */
        array<shared_ptr<array<char,10>>,10>  getGrid();

        /* Setter for @grid */
        void setGrid(array<shared_ptr<array<char,10>>,10> grid);
};
#endif