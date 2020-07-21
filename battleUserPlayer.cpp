#include "battleUserPlayer.h"
#include "textInterface.h"
#include "ship.h"

#include <vector>
#include <iostream>

/* Constructor - passing smart pointer to the player in which this instance is within */
BattleUserPlayer::BattleUserPlayer(const Player* _playerPtr)
{
    playerPtr = _playerPtr;
}

/* Destructor - freeing memory */
BattleUserPlayer::~BattleUserPlayer()
{
    delete playerPtr;
}

/* Returns the raw pointer to the Player object in which this instance is found */
const Player* BattleUserPlayer::getPlayerPtr()
{
    return playerPtr;
}

/* Request the user for a location that they want to use their turn to fire at */
/* Returns the grid location the user chose to fire at */
std::pair<int,int> BattleUserPlayer::takeTurn()
{
    TextInterface::display("Please input the location you wish to fire at on your enemy's grid...");
    int columnEntered = TextInterface::receiveInput("Enter the column: ",int(1));
    int rowEntered = TextInterface::receiveInput("Enter the row: ",int(1));
    
    std::pair<int,int> gridLocationToFireAt = std::make_pair(columnEntered, rowEntered); // https://en.cppreference.com/w/cpp/utility/pair/make_pair
    return gridLocationToFireAt;
}

/* Start @startLocation and end @endLocation locations are passed along with the size of the ship */
/* The function returns a vector of the ship locations that make up the ship that spans from the start location to the end location provided */
std::vector<std::pair<int,int>> getShipLocations(const std::pair<int,int>& startLocation, const std::pair<int,int>& endLocation, int size)
{
    std::vector<std::pair<int,int>> potentialShipLocations;
    
    int startCol = std::get<0>(startLocation);
    int startRow = std::get<1>(startLocation);
    int endCol = std::get<0>(endLocation);
    int endRow = std::get<1>(endLocation);
    
    if(startCol == endCol)
    {
        if(endRow - startRow < 0) // The ship is place vertically down from start location
        {
            //Adding the ship locations to vector
            potentialShipLocations.emplace_back(startLocation);
            for(int i=1; i<size-1; i++)
            {
                std::pair<int,int> location = std::make_pair(startCol, startRow+i);
                potentialShipLocations.emplace_back(location);
            }
            potentialShipLocations.emplace_back(endLocation);
        }
        else // The ship is placed vertically above from start location
        {
            //Adding the ship locations to vector
            potentialShipLocations.emplace_back(startLocation);
            int i=1;
            while(i<size-1)
            {
                std::pair<int,int> location = std::make_pair(startCol, startRow-i);
                potentialShipLocations.emplace_back(location);
                i++;
            }
            potentialShipLocations.emplace_back(endLocation);
        }
    }
    else if(startRow == endRow)
    {
        if(startCol - endCol < 0) // The ship is place horizontally to the right from start location
        {
            //Adding the ship locations to vector
            potentialShipLocations.emplace_back(startLocation);
            for(int i=1; i<size-1; i++)
            {
                std::pair<int,int> location = std::make_pair(startCol+i, startRow);
                potentialShipLocations.emplace_back(location);
            }
            potentialShipLocations.emplace_back(endLocation);
        }
        else // The ship is place horizontally to the left from start location
        {
            //Adding the ship locations to vector
            potentialShipLocations.emplace_back(startLocation);
            int i=1;
            while(i<size-1)
            {
                std::pair<int,int> location = std::make_pair(startCol-i, startRow);
                potentialShipLocations.emplace_back(location);
                i++;
            }
            potentialShipLocations.emplace_back(endLocation);
        }
    }
    return potentialShipLocations;
}

// FRIEND function of Player class
void addToEndingLocationsIfValid(const Player* playerPtr, std::pair<int,int>& startLocation, int valueChanged, char columnOrRowChanged, std::vector<std::pair<int,int>>& availableEndLocations, int size)
{
    if(valueChanged > 0 && valueChanged < 9)
    {
        if(columnOrRowChanged == 'C')
        {            
            std::pair<int,int> endLocation = std::make_pair(valueChanged, std::get<1>(startLocation)); // End location of the ship
                
            std::vector<std::pair<int,int>> potentialShipLocations = getShipLocations(startLocation, endLocation, size); // Locations of the potential ship
            
            // CHECK if conflicting with a ship already placed
            bool shipIsConflicting = false;
            for(Ship ship : playerPtr->ships)
            {
                for(std::vector<std::pair<int,int>>::iterator potentialLocationsIter = potentialShipLocations.begin(); potentialLocationsIter!=potentialShipLocations.end(); std::next(potentialLocationsIter) )
                {
                    shipIsConflicting = ship.isLocationOfShip(*potentialLocationsIter);
                }
            }
            if(!shipIsConflicting) 
                 availableEndLocations.push_back(endLocation);
        }
        else if(columnOrRowChanged == 'R')
        {
            std::pair<int,int> endLocation = std::make_pair(std::get<0>(startLocation),valueChanged); // End location of the ship

            std::vector<std::pair<int,int>> potentialShipLocations = getShipLocations(startLocation, endLocation, size); // Locations of the potential ship

            // CHECK if conflicting with a ship already placed
            bool shipIsConflicting = false;
            for(Ship ship : playerPtr->ships)
            {
                for(std::vector<std::pair<int,int>>::iterator potentialLocationsIter = potentialShipLocations.begin(); potentialLocationsIter!=potentialShipLocations.end(); std::next(potentialLocationsIter) )
                {
                    shipIsConflicting = ship.isLocationOfShip(*potentialLocationsIter);
                }
            }
            if(!shipIsConflicting) 
                availableEndLocations.push_back(endLocation); 
        }
    }                    
                             
}


/* Deals with placing a ship on the player's grid */ 
std::vector<std::pair<int,int>> BattleUserPlayer::placeShip(int size)
{
    // Ask user for ship start location
    TextInterface::display("Please input the starting location of your ship...");
    int columnEntered = TextInterface::receiveInput("Enter the column: ",int(1)); // Input int from user
    int rowEntered = TextInterface::receiveInput("Enter the row: ",int(1)); // Input int from user
    
    std::pair<int,int> startLocation = std::make_pair(columnEntered, rowEntered);
    
    std::vector<std::pair<int,int>> potentialEndLocations;
    
    // Loop to check for 4 potential directions for end location of ship
    // Above, below, to the left of, to the right of the starting location
    for(int i=0; i<4; i++)
    {
        switch(i)
        {
            // Check to the left
            case 0: 
            {
                int endColumn = columnEntered - size;
                addToEndingLocationsIfValid(playerPtr, startLocation, endColumn, 'C', potentialEndLocations, size);
                break;                
            }                
                
            // Check to the right
            case 1: 
            {
                int endColumn = columnEntered + size;
                addToEndingLocationsIfValid(playerPtr, startLocation, endColumn, 'C', potentialEndLocations, size);
                break;
            }
                
            // Check to below
            case 2: 
            {
                int endRow = rowEntered - size;
                addToEndingLocationsIfValid(playerPtr, startLocation, endRow, 'R', potentialEndLocations, size);
                break;
            }
                
            // Check to above
            case 3: 
            {
                int endRow = rowEntered + size;
                addToEndingLocationsIfValid(playerPtr, startLocation, endRow, 'R', potentialEndLocations, size);
                break;
            }
        }       
    }
    
    // Outputting the valid ending locations for the ship and asking the user to choose one of these for their ship
    if(potentialEndLocations.size() > 1)
    {
        // Asking user to choose their ending location of the ship
        TextInterface::display("Here are the options for the end point of your ship:");
        for(int i=0; i<potentialEndLocations.size(); i++)
        {
            std::cout << i << ": (" << std::get<0>(potentialEndLocations[i]) << ", " << std::get<1>(potentialEndLocations[i]) << ")" << std::endl;
        }
        int optionRequested = int(TextInterface::receiveInput("Enter the option you wish to choose: ", int(1)));
        std::pair<int,int> endingLocationChoosen = potentialEndLocations[optionRequested];
        
        return getShipLocations(startLocation, endingLocationChoosen, size);
        
    }
    else
    {
        TextInterface::display("Your starting location is not valid.");
        placeShip(size);
    }
    
}