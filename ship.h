#ifndef SHIP_H
#define SHIP_H

#include <vector>

//Gridlocation library
#include "gridLocation.h"

class Ship
{
    private:        
        // The cells which the ship is placed on, on the grid
        std::vector<GridLocation> shipGridLocations;
        
        // The cells which have been shot at (destroyed)
        std::vector<GridLocation> locationsDestroyed;
        
        /* Method which will be used to determine if a location on a grid is included in a vector of locations */
        bool isGridLocationInVector(vector<GridLocation> gridLocations, GridLocation targetLocation);
    
    public:
        /* Constructor */
        Ship(std::vector<GridLocation> _shipGridLocations);
        
        /* Getter for @shipGridLocations */
        std::vector<GridLocation> getShipLocations();     
        
        /* Returns bool value - true if the ship has been destroyed */
        /* - false if the ship has not been destroyed yet */
        bool isDestroyed();
        
        /* Returns a bool value based on GridLocation @gridLocation passed */
        /* true if @gridLocation is a location which the ship occupies */
        /* false if @gridLocation is not a location that the ship occupies */
        bool isLocationOfShip(GridLocation gridLocation);
        
        /* Adds the @gridLocation GridLocation to vector of locations of the ship which have been destroyed - @locationsDestroyed */
        void addToLocationsDestroyed(GridLocation gridLocation);
        
        // The number of cells the ship will occupy on the grid
        int size();
};
#endif