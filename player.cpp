using namespace std;

#include "player.h"
#include "battleUserPlayer.h"

/* Constructor */
Player::Player(std::string _name, bool isAUser)
{
    name = _name;
    playerGrid = Grid();
    enemyGrid = Grid();
    if(isAUser)
    {
        BattleUserPlayer user = BattleUserPlayer(this);
        role = &user; 
    }        
    else
    {
        // role = IMPLEMENT COMPUTER PLAYER ROLE
    }       
}

/* Destructor */
Player::~Player()
{
    delete role;
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