#include <array>
using namespace std;

// Header file
#include "gridLocation.h"


GridLocation::GridLocation(int _column, int _row)
{
	column = _column;
	row = _row;
}

/* Getter for @column */
int GridLocation::getColumn()
{
	return column;
}

/* Setter for @column */
void GridLocation::setColumn(int _column)
{
	column = _column;
}

/* Getter for @row */
int GridLocation::getRow()
{
	return row;
}

/* Setter for @row */
void GridLocation::setRow(int _row)
{
	row = _row;
}
