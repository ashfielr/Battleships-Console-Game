#include "playerVsPlayer.h"
#include "battleUserPlayer.h"
#include "ship.h"
#include <iostream>

// Waits for player to enter character and press enter untill turn is passed on
void waitForCharacterEntered(std::string message)
{
    char letter2;
    std::cout << message;
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
        player.getEnemyGrid()->alterGridPositionChar('H',row,col);
    else
        player.getEnemyGrid()->alterGridPositionChar('M',row,col);
    
    // Updating the Enemy's grid for the shots they have recieved
    if(shipWasHit)
        enemyPlayer.getOwnGrid()->alterGridPositionChar('H',row,col);
    else
        enemyPlayer.getOwnGrid()->alterGridPositionChar('M',row,col);
    
    return shipWasHit;
}

void displayGrid(const std::shared_ptr<Grid> &gridToDisplay)
{
    std::cout << "[   ] | [ 0 ] [ 1 ] [ 2 ] [ 3 ] [ 4 ] [ 5 ] [ 6 ] [ 7 ] [ 8 ] [ 9 ]" << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;
    for(int row=0; row<10; row++)
    {
        std::cout << "[ " << row << " ] |";
        
        for(int col=0; col<10; col++)
        {
            std::cout << " [ " << gridToDisplay->getGrid()[row][col] << " ]";
        }
        std::cout << std::endl;
    }
}

/* Method deals with an individual player's turn */
/* Returns - true if the player taken a shot that they have not already taken, otherwise it returns false */
bool PlayerVsPlayer::takeTurnForAGivenBattleUserPlayer(BattleUserPlayer &player, int playerNumber, BattleUserPlayer &enemyPlayer)
{
    // Display the grids to the user
    std::cout<< "Your grid: " << std::endl;
    displayGrid(player.getOwnGrid());
    std::cout<< "Your enemy status grid: " << std::endl;
    displayGrid(player.getEnemyGrid());
    
    
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
    
    std::cout<< "Your enemy status grid: " << std::endl;
    displayGrid(player.getEnemyGrid());
    
    return true;
}

/* Method which controls turns */
void PlayerVsPlayer::play()
{
    checkGameOverOrPassTurn("Enter a character and press enter to start your turn PLAYER1.");
    
    std::cout << "PLAYER1: Your turn." << std::endl;    
    while(!takeTurnForAGivenBattleUserPlayer(player1, 1, player2)); // If Player1 has successfully taken a valid shot
    
    checkGameOverOrPassTurn("Enter a character and press enter to pass your turn on.");
    
    checkGameOverOrPassTurn("Enter a character and press enter to start your turn PLAYER2.");
    
    std::cout << "PLAYER2: Your turn." << std::endl;
    while(!takeTurnForAGivenBattleUserPlayer(player2, 1, player1)); // If Player2 has successfully taken a valid shot
    
    checkGameOverOrPassTurn("Enter a character and press enter to pass your turn on.");
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
    
    waitForCharacterEntered("Enter a character and press enter to pass your turn on."); // Waits for player to enter a character then will continue
    
    std::cout << "Player2: you will now place your 5 ships." << std::endl;
    placeShipsForAGivenBattleUserPlayer(player2);
    
    waitForCharacterEntered("Enter a character and press enter to pass your turn on."); // Waits for player to enter a character then will continue
}

// Will check if the game has ended after a player's turn and wait until they have confirmed to move onto the next player
void PlayerVsPlayer::checkGameOverOrPassTurn(std::string waitForCharMessage)
{
    if(isGameOver())
    {
        std::cout << "You won!" << std:: endl; 
        return;
    }
           
    waitForCharacterEntered(waitForCharMessage); // Waits for player to enter a character then will continue
}