using namespace std;

#include "player.h"
#include "battleUserPlayer.h"

#include <iostream>

/* Constructors */
Player::Player()
{
    
}

Player::Player(std::string _name)
{
    name = _name;
    playerGrid = Grid();
    enemyGrid = Grid();      
}

/* Returns the player's name */
string Player::getName() const
{
    return name;
}

/* Allows the player's name to be changed */
void Player::setName(std::string _name)
{
    name = _name;
}

/* Returns true if all of the player's ships have been destroyed and flase if not */
bool Player::isAllShipsDestroyed() const
{
    bool allShipsDestroyed = true;
    for(Ship ship : ships)
    {
        if(!ship.isDestroyed())
            allShipsDestroyed = false;
    }
    return allShipsDestroyed;
}

/* Returns the player's ships */
std::vector<Ship> Player::getShips() const
{
    return ships;
}

/* Adds a ship to player */
void Player::addShip(Ship shipToAdd)
{
    ships.emplace_back(shipToAdd);
}

/* Returns the player's grid */
Grid Player::getOwnGrid() const
{
    return playerGrid;
}

/* Returns the player's version of enemy grid */
Grid Player::getEnemyGrid() const
{
    return enemyGrid;
}