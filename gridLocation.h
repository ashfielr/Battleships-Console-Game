#ifndef GRIDLOCATION_H
#define GRIDLOCATION_H

#include <array>
using namespace std;

class GridLocation
{
    private:
        // The column number
        int column;

        // The row number
        int row;
		
    public:
        GridLocation(int _column, int _row);

        /* Getter for @column */
        int getColumn();

        /* Setter for @column */
        void setColumn(int _column);
		
		/* Getter for @row */
        int getRow();

        /* Setter for @row */
        void setRow(int _row);
};
#endif