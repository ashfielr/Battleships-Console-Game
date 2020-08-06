#ifndef SHIP_H
#define SHIP_H

#include <vector>

/* The Ship class encapsulates all of the data and functionality invovled around a Ship on a Player's grid */
class Ship
{
    private:        
        /* The cells which the ship is placed on, on the grid */
        std::vector<std::pair<int,int>> shipGridLocations;
        
        /* The cells which have been shot at (destroyed) */
        std::vector<std::pair<int,int>> locationsDestroyed;
        
        /* Method which will be used to determine if a location on a grid is included in a vector of locations */
        const bool isGridLocationInVector(std::vector<std::pair<int,int>> gridLocations, std::pair<int,int> targetLocation);
    
    public:
        /* Constructor */
        Ship(std::vector<std::pair<int,int>> _shipGridLocations);
        
        /* Getter for @shipGridLocations */
        std::vector<std::pair<int,int>> getShipLocations();     
        
        /* Returns bool value - true if the ship has been destroyed */
        /* - false if the ship has not been destroyed yet */
        bool isDestroyed();
        
        /* Returns a bool value based on @gridLocation location passed */
        /* true if @gridLocation is a location which the ship occupies */
        /* false if @gridLocation is not a location that the ship occupies */
        const bool isLocationOfShip(std::pair<int,int> gridLocation);
        
        /* Returns a bool value - true if the location passed ( @gridLocation ) is a location destroyed already */
        /* Returns a bool value - false if the location passed ( @gridLocation ) is not a location destroyed already */
        const bool isLocationAlreadyDestroyed(std::pair<int,int> gridLocation);
        
        /* Adds the @gridLocation locaiton to vector of locations of the ship which have been destroyed - @locationsDestroyed */
        void addToLocationsDestroyed(const std::pair<int,int>& gridLocation);
        
        // The number of cells the ship will occupy on the grid
        int size();
};
#endif