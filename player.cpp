using namespace std;

#include "player.h"

/* Constructor */
Player::Player(std::string _name)
{
    name = _name;
    playerGrid = Grid();
    enemyGrid = Grid();
}

/* Returns the player's name */
string Player::getName()
{
    return name;
}
        
/* Allows the player's name to be changed */
void Player::setName(std::string _name)
{
    name = _name;
}