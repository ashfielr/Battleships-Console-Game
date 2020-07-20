using namespace std;

//Ship library to be implemented
#include "ship.h"

#include <utility> // To use std::get to get an element from a std::pair

/* Constructor for Ship class */
/* @_shipGridLocations is the vector of locations that make up the ship */
Ship::Ship(vector<std::pair<int,int>> _shipGridLocations)
{
    shipGridLocations = _shipGridLocations;
}

/* Takes a vector and a target grid location and checks if it is present in the vector */
bool Ship::isGridLocationInVector(vector<std::pair<int,int>> gridLocations, std::pair<int,int> targetLocation)
{
    for(vector<std::pair<int,int>>::iterator it=gridLocations.begin(); it!=gridLocations.end(); next(it))
    {
        if(std::get<1>(*it) == std::get<1>(targetLocation) && std::get<0>(*it) == std::get<1>(targetLocation)) // https://en.cppreference.com/w/cpp/utility/pair/get
            return true;
    }
    return false;
}

/* Returns the vector of locations that make up the ship */
vector<std::pair<int,int>> Ship::getShipLocations()
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
bool Ship::isLocationOfShip(const std::pair<int,int>& gridLocation)
{
    isGridLocationInVector(shipGridLocations, gridLocation);
}

/* When a ship location has been fired it is destroyed */
/* This method added the location that has been destroyed to the list of destroyed locations */
void Ship::addToLocationsDestroyed(const std::pair<int,int>& gridLocation)
{
    // Add code here to add location to vector of destroyed locations
}

/* Returns the size of the ship */
int Ship::size()
{
    return shipGridLocations.size();
}