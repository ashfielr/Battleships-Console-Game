using namespace std;

//Ship library to be implemented
#include "ship.h"

/* Constructor for Ship class */
/* @_shipGridLocations is the vector of locations that make up the ship */
Ship::Ship(vector<GridLocation> _shipGridLocations)
{
    shipGridLocations = _shipGridLocations;
}

/* Takes a vector and a target grid location and checks if it is present in the vector */
bool Ship::isGridLocationInVector(vector<GridLocation> gridLocations, GridLocation targetLocation)
{
    for(vector<GridLocation>::iterator it=gridLocations.begin(); it!=gridLocations.end(); next(it))
    {
        if(it->getRow() == targetLocation.getRow() && it->getColumn() == targetLocation.getColumn())
            return true;
    }
    return false;
}

/* Returns the vector of locations that make up the ship */
vector<GridLocation> Ship::getShipLocations()
{
    return shipGridLocations;
}

/* Returns a true bool false if the ship has been destroyed otherwise returns false */
bool Ship::isDestroyed()
{
    if(locationsDestroyed.size() == this->size())
    {
        for(int i=0; i<this->size(); i++)
        {
            if( isGridLocationInVector(shipGridLocations, locationsDestroyed[i]) == false )
                return false;
        }
        return true;
    }
    return false; 
    
}

/* Returns a bool value - true if the location passed ( @gridLocation ) is a location belonging to the ship */
/* Returns a bool value - false if the location passed ( @gridLocation ) is not a location belonging to the ship */
bool Ship::isLocationOfShip(GridLocation gridLocation)
{
    isGridLocationInVector(shipGridLocations, gridLocation);
}

/* When a ship location has been fired it is destroyed */
/* This method added the location that has been destroyed to the list of destroyed locations */
void Ship::addToLocationsDestroyed(GridLocation gridLocation)
{
    // Add code here to add location to vector of destroyed locations
}

/* Returns the size of the ship */
int Ship::size()
{
    return shipGridLocations.size();
}