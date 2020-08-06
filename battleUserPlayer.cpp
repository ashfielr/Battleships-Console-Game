#include "battleUserPlayer.h"
#include "textInterface.h"
#include "ship.h"

/* Constructor */
BattleUserPlayer::BattleUserPlayer()
{
    
}

/* Request the user for a location that they want to use their turn to fire at */
/* Returns the grid location the user chose to fire at */
std::pair<int,int> BattleUserPlayer::takeTurn()
{
    int columnEntered = TextInterface::receiveIntInput("Please input the location you wish to fire at on your enemy's grid...\nEnter the column: ");    
    int rowEntered = TextInterface::receiveIntInput("Enter the row: ");
    
    std::pair<int,int> gridLocationToFireAt = std::make_pair(columnEntered, rowEntered); // Using std::pair data structure https://en.cppreference.com/w/cpp/utility/pair/make_pair

    return gridLocationToFireAt;
}

/* Start @startLocation and end @endLocation locations are passed along with the size of the ship */
/* The function returns a vector of the ship locations that make up the ship that spans from the start location to the end location provided */
/* Note: this is a function used to break down tasks (it is not a method of the class) */
std::vector<std::pair<int,int>> getShipLocations(const std::pair<int,int>& startLocation, const std::pair<int,int>& endLocation, int size)
{
    std::vector<std::pair<int,int>> potentialShipLocations;
    
    int startCol = std::get<0>(startLocation);
    int startRow = std::get<1>(startLocation);
    int endCol = std::get<0>(endLocation);
    int endRow = std::get<1>(endLocation);
    
    if(startCol == endCol)
    {
        if(startRow - endRow < 0) // The ship is placed vertically down from start location
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

/* This function will add a grid location for an end point of a ship to a collection of grid locations if it is a valid ending point for a ship with the @startLocation provided */
/* Note: this is a function used to break down tasks (it is not a method of the class) */
void addToEndingLocationsIfValid(std::vector<std::shared_ptr<Ship>> &_ships, std::pair<int,int> &startLocation, int valueChanged, char columnOrRowChanged, std::vector<std::pair<int,int>> &availableEndLocations, int size)
{
    if(valueChanged >= 0 && valueChanged <= 9)
    {
        if(columnOrRowChanged == 'C')
        {            
            std::pair<int,int> endLocation = std::make_pair(valueChanged, std::get<1>(startLocation)); // End location of the ship
                
            std::vector<std::pair<int,int>> potentialShipLocations = getShipLocations(startLocation, endLocation, size); // Locations of the potential ship
            
            // CHECK if conflicting with a ship already placed
            for(std::shared_ptr<Ship> ship : _ships)
            {
                for(unsigned i=0; i<potentialShipLocations.size(); i++)
                {                   
                    if(ship->isLocationOfShip(potentialShipLocations[i])) // Not a valid ending location so do not add
                        return;
                }
            }
            // No ships are conflicting with this so add to colleciton of end locations available
            availableEndLocations.push_back(endLocation); 
        }
        else if(columnOrRowChanged == 'R')
        {
            std::pair<int,int> endLocation = std::make_pair(std::get<0>(startLocation),valueChanged); // End location of the ship

            std::vector<std::pair<int,int>> potentialShipLocations = getShipLocations(startLocation, endLocation, size); // Locations of the potential ship

            // CHECK if conflicting with a ship already placed
            for(std::shared_ptr<Ship> ship : _ships)
            {
                for(unsigned i=0; i<potentialShipLocations.size(); i++)
                {                    
                    if(ship->isLocationOfShip(potentialShipLocations[i])) // Not a valid ending location so do not add
                        return;
                }
            }
            // No ships are conflicting with this so add to colleciton of end locations available
            availableEndLocations.push_back(endLocation); 
        }
    }                    
                             
}


/* Deals with placing a ship on the player's grid */ 
std::vector<std::pair<int,int>> BattleUserPlayer::placeShip(int size)
{
    std::vector<std::pair<int,int>> shipLocationsToReturn;
    
    bool validStartingLocationEntered = false;
    int columnEntered;
    int rowEntered;
    while(!validStartingLocationEntered)
    {
        columnEntered = TextInterface::receiveIntInput("Please input the location you wish to be the start of your ship...\nEnter the column: ");  
        rowEntered = TextInterface::receiveIntInput("Enter the row: ");
        
        if(columnEntered >= 0 & columnEntered <= 9 & rowEntered >= 0 & rowEntered <=9)
            validStartingLocationEntered = true;
        else
            TextInterface::display("Invalid starting location.");
    }
  
    
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
                int endColumn = columnEntered - size + 1;
                addToEndingLocationsIfValid(this->ships, startLocation, endColumn, 'C', potentialEndLocations, size);
                break;                
            }                
                
            // Check to the right
            case 1: 
            {               
                int endColumn = columnEntered + size - 1;
                addToEndingLocationsIfValid(this->ships, startLocation, endColumn, 'C', potentialEndLocations, size);               
                break;
            }
                
            // Check to below
            case 2: 
            {
                int endRow = rowEntered - size + 1;
                addToEndingLocationsIfValid(this->ships, startLocation, endRow, 'R', potentialEndLocations, size);
                break;
            }
                
            // Check to above
            case 3: 
            {
                int endRow = rowEntered + size - 1;
                addToEndingLocationsIfValid(this->ships, startLocation, endRow, 'R', potentialEndLocations, size);
                break;
            }
        }       
    }
    
    // Outputting the valid ending locations for the ship and asking the user to choose one of these for their ship
    if(potentialEndLocations.size() >= 1)
    {
        int optionRequested; 
        bool validOptionSelected = false;
        do
        {
            // Asking user to choose their ending location of the ship
            TextInterface::display("\nHere are the options for the end point of your ship:");
            for(unsigned i=0; i<potentialEndLocations.size(); i++)
            {
                /// #### REFERENCE START - Found std::to_string() from the forum page answer: https://stackoverflow.com/a/10516313 #######
                std::string option = std::to_string(i) + ": (" + std::to_string(std::get<0>(potentialEndLocations[i])) + ", " + std::to_string(std::get<1>(potentialEndLocations[i])) + ")";
                /// #### REFERENCE END - Found std::to_string() from the forum page answer: https://stackoverflow.com/a/10516313 #######
                
                TextInterface::display(option);
            }
            
            optionRequested = TextInterface::receiveIntInput("Enter the option you wish to choose: "); // Asking user to choose one

            if(optionRequested >= 0 && optionRequested < potentialEndLocations.size())
                validOptionSelected = true;
            else
                TextInterface::display("That is not an option - enter one of the options.");
        } while(!validOptionSelected);
        
        
        std::pair<int,int> endingLocationChoosen = potentialEndLocations[optionRequested]; 
        
        shipLocationsToReturn = getShipLocations(startLocation, endingLocationChoosen, size); // The locations of the ship to be placed 
    }
    else
    {
        TextInterface::display("Your starting location is not valid.");
        shipLocationsToReturn = placeShip(size); // RECURSION - repeat method until a valid starting location is entered and ending location chosen
    }
    
    return shipLocationsToReturn;
}