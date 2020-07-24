#ifndef BATTLEUSERPLAYER_H
#define BATTLEUSERPLAYER_H

#include<vector>
#include<utility>

#include "player.h"

/* Class with functionality for a user player (human) to play their role as a player */
class BattleUserPlayer : public Player
{
    public:
        /* Constructor */
        BattleUserPlayer();
    
        /* All of the necessary actions are carried out for the player's turn to be completed */
        std::pair<int,int> takeTurn();
        
        /* Deals with placing a ship on the player's grid */ 
        std::vector<std::pair<int,int>> placeShip(int size);
};
#endif