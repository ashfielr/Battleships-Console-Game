#include "playerVsPlayer.h"
#include "battleUserPlayer.h"
#include "ship.h"
#include "textInterface.h"

// Waits for player to enter character and press enter untill turn is passed on
void waitForCharacterEntered(std::string message)
{
    TextInterface::receiveCharInput(message);
    
    for(int i=0; i<10; i++)
    {
        TextInterface::display("\n\n\n\n\n\n\n\n");
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
                TextInterface::display("Ship destroyed!");
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

/* Method deals with an individual player's turn */
/* Returns - true if the player taken a shot that they have not already taken, otherwise it returns false */
bool PlayerVsPlayer::takeTurnForAGivenBattleUserPlayer(BattleUserPlayer &player, int playerNumber, BattleUserPlayer &enemyPlayer)
{
    // Display the grids to the user
    TextInterface::display("Your grid: ");
    TextInterface::display(player.getOwnGrid());
    TextInterface::display("Your enemy status grid: ");
    TextInterface::display(player.getEnemyGrid());
    
    
    bool gameOver = false;
    std::pair<int,int> shotTakenP1 = player.takeTurn();
    
    //Check if the location has already been shot at
    for(int i=0; i<player.getGridLocationsShotAt().size(); i++)
    {
        // If they have already shot at that location
        if(std::get<0>(player.getGridLocationsShotAt()[i]) == std::get<0>(shotTakenP1) && std::get<1>(player.getGridLocationsShotAt()[i]) == std::get<1>(shotTakenP1))
        {
            TextInterface::display("You have already shot at that location...");
            return false;
        }
    }
    
    player.addToLocationsShotAt(shotTakenP1);
        
    if(updateGridsAndShips(shotTakenP1, player, enemyPlayer))
        TextInterface::display("HIT");
    else
        TextInterface::display("MISS");
    
    TextInterface::display("Your enemy status grid: ");
    TextInterface::display(player.getEnemyGrid());
    
    return true;
}

/* Method which controls turns */
void PlayerVsPlayer::play()
{
    checkGameOverOrPassTurn("Enter a character and press enter to start your turn PLAYER1.");
    
    TextInterface::display("PLAYER1: Your turn.");    
    while(!takeTurnForAGivenBattleUserPlayer(player1, 1, player2)); // If Player1 has successfully taken a valid shot
    
    if(checkGameOverOrPassTurn("Enter a character and press enter to pass your turn on."))
        return;
    
    checkGameOverOrPassTurn("Enter a character and press enter to start your turn PLAYER2.");
    
    TextInterface::display("PLAYER2: Your turn.");
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
        TextInterface::display("Your current grid: "); 
        TextInterface::display(player.getOwnGrid());
        
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
    TextInterface::display("Player1: you will now place your 5 ships.");
    placeShipsForAGivenBattleUserPlayer(player1);
    
    waitForCharacterEntered("Enter a character and press enter to pass your turn on."); // Waits for player to enter a character then will continue
    
    TextInterface::display("Player2: you will now place your 5 ships.");
    placeShipsForAGivenBattleUserPlayer(player2);
    
    waitForCharacterEntered("Enter a character and press enter to pass your turn on."); // Waits for player to enter a character then will continue
}

// Will check if the game has ended after a player's turn and wait until they have confirmed to move onto the next player
// Returns true if the game is over, returns false if the game is not over
bool PlayerVsPlayer::checkGameOverOrPassTurn(std::string waitForCharMessage)
{
    if(isGameOver())
    {
        TextInterface::display("You won!"); 
        return true;
    }
           
    waitForCharacterEntered(waitForCharMessage); // Waits for player to enter a character then will continue
    return false;
}