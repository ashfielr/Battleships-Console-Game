#include "battle.h"

/* Constructor */
Battle::Battle(bool p1IsAUser, bool p2IsAUser)
{
    player1 = std::make_shared<Player>(Player("Player 1", p1IsAUser));
    player2 = std::make_shared<Player>(Player("Player 2", p2IsAUser));
}

bool Battle::isGameOver()
{
    // Return bool whether game is finished
}

/* Method to update the Grids after a location has been choosen for a player's turn */
void Battle::updateGrids(std::pair<int,int> gridLocationToUpdate, const Player& player, const Player& enemyPlayer)
{
    
}

/* Method to update hit locations of enemy ships after a location has been choosen for a player's turn */
void Battle::updateGrids(std::pair<int,int> gridLocationToShootAt, const Player& enemyPlayer)
{
    
}

/* Method which controls turns */
void Battle::play()
{
    player1->getRole()->takeTurn();
}