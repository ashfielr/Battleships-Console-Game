#include "battleUserPlayer.h"
#include "textInterface.h"

#include <vector>


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

/* Deals with placing a ship on the player's grid */ 
std::vector<std::pair<int,int>> BattleUserPlayer::placeShip(int size)
{
     // ADD CODE HERE   
}