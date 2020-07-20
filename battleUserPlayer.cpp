#include "battleUserPlayer.h"
#include "textInterface.h"

#include <vector>

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


/* Deals with placing a ship on the player's grid */ 
std::vector<std::pair<int,int>> BattleUserPlayer::placeShip(int size)
{
     // ADD CODE HERE   
}