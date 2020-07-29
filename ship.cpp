//Ship library to be implemented
#include "ship.h"

#include <utility> // To use std::get to get an element from a std::pair

/* Constructor for Ship class */
/* @_shipGridLocations is the vector of locations that make up the ship */
Ship::Ship(std::vector<std::pair<int,int>> _shipGridLocations)
{
    shipGridLocations = _shipGridLocations;
}

/* Takes a vector and a target grid location and checks if it is present in the vector */
const bool Ship::isGridLocationInVector(std::vector<std::pair<int,int>> gridLocations, std::pair<int,int> targetLocation)
{
    for(unsigned i=0; i<gridLocations.size(); i++)
    {       
        if(std::get<1>(gridLocations[i]) == std::get<1>(targetLocation) && std::get<0>(gridLocations[i]) == std::get<0>(targetLocation)) // https://en.cppreference.com/w/cpp/utility/pair/get
            return true;
    }
    return false;
}

/* Returns the vector of locations that make up the ship */
std::vector<std::pair<int,int>> Ship::getShipLocations()
{
    return shipGridLocations;
}

/* Returns a true bool false if the ship has been destroyed otherwise returns false */
bool Ship::isDestroyed()
{
    if(locationsDestroyed.size() == (unsigned)this->size()) // Had warning with comparison between unsigned and signed so this page helped me fix the warning - https://stackoverflow.com/questions/3660901/a-warning-comparison-between-signed-and-unsigned-integer-expressions
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
const bool Ship::isLocationOfShip(std::pair<int,int> gridLocation)
{
    return isGridLocationInVector(shipGridLocations, gridLocation);
}

/* Returns a bool value - true if the location passed ( @gridLocation ) is a location destroyed already */
/* Returns a bool value - false if the location passed ( @gridLocation ) is not a location destroyed already */
const bool Ship::isLocationAlreadyDestroyed(std::pair<int,int> gridLocation)
{
    return isGridLocationInVector(locationsDestroyed, gridLocation);
}

/* When a ship location has been fired it is destroyed */
/* This method added the location that has been destroyed to the list of destroyed locations */
void Ship::addToLocationsDestroyed(const std::pair<int,int> &gridLocationHit)
{
    locationsDestroyed.emplace_back(gridLocationHit);
}

/* Returns the size of the ship */
int Ship::size()
{
    return shipGridLocations.size();
}