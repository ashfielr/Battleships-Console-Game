#include "battleUserPlayer.h"
#include "textInterface.h"
#include "ship.h"

#include <iostream>

/* Constructor */
BattleUserPlayer::BattleUserPlayer()
{
    
}

/* Request the user for a location that they want to use their turn to fire at */
/* Returns the grid location the user chose to fir e at */
std::pair<int,int> BattleUserPlayer::takeTurn()
{
    /*TextInterface::display("Please input the location you wish to fire at on your enemy's grid...");
    int columnEntered = TextInterface::receiveInput("Enter the column: ",int(1));
    int rowEntered = TextInterface::receiveInput("Enter the row: ",int(1));
    */
    std::cout << "Please input the location you wish to fire at on your enemy's grid..." << std::endl;
    std::cout << "Enter the column: " << std::endl;
    int columnEntered;
    std:: cin >> columnEntered;
    
    std::cout << "Enter the row: " << std::endl;
    int rowEntered;
    std::cin >> rowEntered;
    
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
        if(startRow - endRow < 0) // The ship is place vertically down from start location
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
                    // ##################################################################std::cout << "Ship conflicting: " << ship.isLocationOfShip(potentialShipLocations[i]) << std::endl;// ########################################
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
                    // ##################################################################std::cout << "Ship conflicting: " << ship.isLocationOfShip(potentialShipLocations[i]) << std::endl;
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
    // Ask user for ship start location
    /*TextInterface::display("Please input the starting location of your ship...");
    int columnEntered = TextInterface::receiveInput("Enter the column: ",int(1)); // Input int from user
    int rowEntered = TextInterface::receiveInput("Enter the row: ",int(1)); // Input int from user
    */
    std::vector<std::pair<int,int>> shipLocationsToReturn;
    
    bool validStartingLocationEntered = false;
    int columnEntered;
    int rowEntered;
    while(!validStartingLocationEntered)
    {
        std::cout << "\n\nPlease input the starting location of your ship - Size: " << size << std::endl;
        std::cout << "Enter the column: " << std::endl; 
        std:: cin >> columnEntered;
    
        std::cout << "Enter the row: " << std::endl;
        std::cin >> rowEntered;  
        
        if(columnEntered >= 0 & columnEntered <= 9 & rowEntered >= 0 & rowEntered <=9)
            validStartingLocationEntered = true;
        else
            std::cout << "Invalid starting location." << std::endl;
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
                //std::cout << "Check L" << std::endl; ##################################
                int endColumn = columnEntered - size + 1;
                addToEndingLocationsIfValid(this->ships, startLocation, endColumn, 'C', potentialEndLocations, size);
                break;                
            }                
                
            // Check to the right
            case 1: 
            {
                //std::cout << "Check R" << std::endl; //##################################
                int endColumn = columnEntered + size - 1;
                addToEndingLocationsIfValid(this->ships, startLocation, endColumn, 'C', potentialEndLocations, size);               
                break;
            }
                
            // Check to below
            case 2: 
            {
                //std::cout << "Check D" << std::endl; ##################################
                int endRow = rowEntered - size + 1;
                addToEndingLocationsIfValid(this->ships, startLocation, endRow, 'R', potentialEndLocations, size);
                break;
            }
                
            // Check to above
            case 3: 
            {
                //std::cout << "Check U" << std::endl; //##################################
                int endRow = rowEntered + size - 1;
                addToEndingLocationsIfValid(this->ships, startLocation, endRow, 'R', potentialEndLocations, size);
                break;
            }
        }       
    }
    
    // Outputting the valid ending locations for the ship and asking the user to choose one of these for their ship
    if(potentialEndLocations.size() >= 1)
    {
        bool validOptionSelected = false;
        int optionRequested;
        do
        {
            // Asking user to choose their ending location of the ship
            std::cout << "\nHere are the options for the end point of your ship:" << std::endl;
            for(unsigned i=0; i<potentialEndLocations.size(); i++)
            {
                std::cout << i << ": (" << std::get<0>(potentialEndLocations[i]) << ", " << std::get<1>(potentialEndLocations[i]) << ")" << std::endl;
            }
            ////####int optionRequested = int(TextInterface::receiveInput("Enter the option you wish to choose: ", int(1)));
            std::cout << "Enter the option you wish to choose: " << std::endl;
            std::cin >> optionRequested;

            if(optionRequested >= 0 && optionRequested < potentialEndLocations.size())
                validOptionSelected = true;
            else
                std::cout << "That is not an option. Please enter one of the options." << std::endl;
        } while(!validOptionSelected);
        
        
        std::pair<int,int> endingLocationChoosen = potentialEndLocations[optionRequested]; 
        
        shipLocationsToReturn = getShipLocations(startLocation, endingLocationChoosen, size); // The locations of the ship to be placed 
    }
    else
    {
        std::cout << "Your starting location is not valid." << std::endl;
        shipLocationsToReturn = placeShip(size); // RECURSION - repeat until a valid starting location is entered and ending location chosen
    }
    
    return shipLocationsToReturn;
}