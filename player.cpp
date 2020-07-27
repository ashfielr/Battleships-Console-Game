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
    for(std::shared_ptr<Ship> ship : ships)
    {
        if(!ship->isDestroyed())
            allShipsDestroyed = false;
    }
    return allShipsDestroyed;
}

/* Returns the player's ships */
std::vector<std::shared_ptr<Ship>> Player::getShips() const
{
    return ships;
}

/* Adds a ship to player */
void Player::addShip(Ship shipToAdd)
{
    std::shared_ptr<Ship> shipToAddPtr = std::make_shared<Ship>(shipToAdd);
    ships.emplace_back(shipToAddPtr); // Adding ship objects
    
    // Adding the ship to player's grid (each location marked with 'X' character)
    for(unsigned i=0; i<shipToAdd.getShipLocations().size(); i++)
    {
        int row = std::get<1>(shipToAdd.getShipLocations()[i]);
        int col = std::get<0>(shipToAdd.getShipLocations()[i]);
        playerGrid.alterGridPositionChar('X', row, col);
    }
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

/* Returns the grid locations the player has shot at */
std::vector<std::pair<int,int>> Player::getGridLocationsShotAt() const
{
    return gridLocationsShotAt;
}

/* Adds location to the grid locations the player has shot at */
void Player::addToLocationsShotAt(std::pair<int,int> location)
{
    gridLocationsShotAt.emplace_back(location);
}