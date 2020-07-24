#include "playerVsPlayer.h"
#include "battleUserPlayer.h"




#include "ship.h"
#include <iostream>




// Constructor
PlayerVsPlayer::PlayerVsPlayer()
{
    
}

// Return bool whether game is finished
bool PlayerVsPlayer::isGameOver()
{
    return (player1.isAllShipsDestroyed() || player2.isAllShipsDestroyed());
}

/* Method to update the Grids after a location has been choosen for a player's turn */
void PlayerVsPlayer::updateGridsAndShips(const std::pair<int,int> &gridLocationToUpdate, const Player& player, const Player& enemyPlayer)
{
    // Updating the Player's status grid for the shots they have fired
    bool shipWasHit = false;
    for(Ship enemyShip : enemyPlayer.getShips()) // For each Ship belonging to the enemy player
    {
        if(enemyShip.isLocationOfShip(gridLocationToUpdate)) // If the player hit a ship
        {            
            enemyShip.addToLocationsDestroyed(gridLocationToUpdate); // Add to locaitons destroyed on the ship instance
            shipWasHit = true;
        }
    }
   
    int row = std::get<1>(gridLocationToUpdate);
    int col = std::get<0>(gridLocationToUpdate);
    
    if(shipWasHit)
        player.getEnemyGrid().getGrid()[row][col] = 'H';
    else
        player.getEnemyGrid().getGrid()[row][col] = 'M';
    
    // Updating the Enemy's grid for the shots they have recieved
    if(shipWasHit)
        enemyPlayer.getOwnGrid().getGrid()[row][col] = 'H';
    else
        enemyPlayer.getOwnGrid().getGrid()[row][col] = 'M';
}

/* Method which controls turns */
void PlayerVsPlayer::play()
{
    std::pair<int,int> shotTakenP1 = player1.takeTurn();
    updateGridsAndShips(shotTakenP1, player1, player2);
    
    if(isGameOver())
        return;
    
    std::pair<int,int> shotTakenP2 = player1.takeTurn();
    updateGridsAndShips(shotTakenP2, player2, player1);
}

/* Method which controls turns */
void PlayerVsPlayer::placeShips()
{
    player1.addShip(player1.placeShip(5));
    //std::cout << "No Ships: " << player1.getShips().size();
    
    /*for(Ship _ship : player1.getShips())
    {
        for(unsigned i=0; i<_ship.getShipLocations().size(); i++)
        {
            std::cout << std::get<0>(_ship.getShipLocations()[i]) << ", " << std::get<1>(_ship.getShipLocations()[i]) << "     ";
        }
        std::cout << std::endl;
    }
    std::cout << "\n" << std::endl;
    */
    
    player1.addShip(player1.placeShip(4));
    //std::cout << "No Ships: " << player1.getShips().size();
    
    
    player1.addShip(player1.placeShip(3));    
    //std::cout << "No Ships: " << player1.getShips().size() << std::endl;
    
    
    //std::cout << "\n" << std::endl;
    player1.addShip(player1.placeShip(3));
    player1.addShip(player1.placeShip(2));
    
    player2.addShip(player2.placeShip(5));
    player2.addShip(player2.placeShip(4));
    player2.addShip(player2.placeShip(3));
    player2.addShip(player2.placeShip(3));
    player2.addShip(player2.placeShip(2));
}