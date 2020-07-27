#include "playerVsPlayer.h"
#include "battleUserPlayer.h"




#include "ship.h"
#include <iostream>


void passTurn()
{
    char letter2;
    std::cout << "Enter a character then press enter to pass the turn on: ";
    std::cin  >> letter2;
    
    for(int i=0; i<10; i++)
    {
        std::cout << "\n\n\n\n\n\n\n\n" << std::endl;
    }
}


// Constructor
PlayerVsPlayer::PlayerVsPlayer()
{
    
}

// Return bool whether game is finished
bool PlayerVsPlayer::isGameOver()
{
    return (player2.isAllShipsDestroyed() || player1.isAllShipsDestroyed());
}

/* Method to update the Grids and Ships after a location has been choosen for a player's turn */
/* Returns - true if ship was hit, false if a ship was not hit */
bool PlayerVsPlayer::updateGridsAndShips(const std::pair<int,int> &gridLocationToUpdate, const Player& player, const Player& enemyPlayer)
{
    // Updating the Player's status grid for the shots they have fired
    bool shipWasHit = false;
    bool shipWasDestroyed = false;
    for(std::shared_ptr<Ship> enemyShip : enemyPlayer.getShips()) // For each Ship belonging to the enemy player
    {
        if(enemyShip->isLocationOfShip(gridLocationToUpdate) && !enemyShip->isLocationAlreadyDestroyed(gridLocationToUpdate)) // If the player hit a ship
        {            
            enemyShip->addToLocationsDestroyed(gridLocationToUpdate); // Add to locaitons destroyed on the ship instance  
            shipWasHit = true;
            if(enemyShip->isDestroyed())
                std::cout << "Ship destroyed!" << std::endl;
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
    
    return shipWasHit;
}

void displayGrid(const Grid &gridToDisplay)
{
    std::cout << "[   ] | [ 0 ] [ 1 ] [ 2 ] [ 3 ] [ 4 ] [ 5 ] [ 6 ] [ 7 ] [ 8 ] [ 9 ]" << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;
    for(int row=0; row<10; row++)
    {
        std::cout << "[ " << row << " ] |";
        
        for(int col=0; col<10; col++)
        {
            std::cout << " [ " << gridToDisplay.getGrid()[row][col] << " ]";
        }
        std::cout << std::endl;
    }
}

/* Method deals with an individual player's turn */
/* Returns - true if the player taken a shot that they have not already taken, otherwise it returns false */
bool PlayerVsPlayer::takeTurnForAGivenBattleUserPlayer(BattleUserPlayer &player, int playerNumber, BattleUserPlayer &enemyPlayer)
{
    bool gameOver = false;
    std::pair<int,int> shotTakenP1 = player.takeTurn();
    
    //Check if the location has already been shot at
    for(int i=0; i<player.getGridLocationsShotAt().size(); i++)
    {
        // If they have already shot at that location
        if(std::get<0>(player.getGridLocationsShotAt()[i]) == std::get<0>(shotTakenP1) && std::get<1>(player.getGridLocationsShotAt()[i]) == std::get<1>(shotTakenP1))
        {
            std::cout << "You have already shot at that location..." << std::endl;
            return false;
        }
    }
    
    player.addToLocationsShotAt(shotTakenP1);
        
    if(updateGridsAndShips(shotTakenP1, player, enemyPlayer))
        std::cout << "HIT" << std::endl;
    else
        std::cout << "MISS" << std::endl;
    
    return true;
}

/* Method which controls turns */
void PlayerVsPlayer::play()
{
    std::cout << "PLAYER1: Your turn." << std::endl;
    while(!takeTurnForAGivenBattleUserPlayer(player1, 1, player2)); // If Player1 has successfully taken a valid shot
    if(isGameOver())
        std::cout << "You won!" << std:: endl;
           
    passTurn(); // Waits for player to enter a character then will continue
    
    std::cout << "PLAYER2: Your turn." << std::endl;
    while(!takeTurnForAGivenBattleUserPlayer(player2, 1, player1)); // If Player2 has successfully taken a valid shot
    if(isGameOver())
        std::cout << "You won!" << std:: endl;       
        
    passTurn(); // Waits for player to enter a character then will continue
}

void PlayerVsPlayer::placeShipsForAGivenBattleUserPlayer(BattleUserPlayer &player)
{
    bool shipOfSize3Placed = false;
    for(int sizeOfShip=5; sizeOfShip >=2; sizeOfShip--)
    {
        player.addShip(player.placeShip(sizeOfShip)); //Add ship to player and player's grid
        // Display the player's grid after ship has been placed
        std::cout << "Your current grid: " << std::endl; 
        displayGrid(player.getOwnGrid());
        
        if(sizeOfShip==3 && !shipOfSize3Placed) // Will allow two ships of size 3 to be placed
        {
            shipOfSize3Placed = true;
            sizeOfShip++;
        }            
    }
}

/* Method which controls placing ships at start for both players */
void PlayerVsPlayer::placeShips()
{
    std::cout << "Player1: you will now place your 5 ships." << std::endl;
    placeShipsForAGivenBattleUserPlayer(player1);
    
    passTurn(); // Waits for player to enter a character then will continue
    
    std::cout << "Player2: you will now place your 5 ships." << std::endl;
    placeShipsForAGivenBattleUserPlayer(player2);
    
    passTurn(); // Waits for player to enter a character then will continue
}