#ifndef BATTLEUSERPLAYER_H
#define BATTLEUSERPLAYER_H

#include "iBattlePlayerRole.h"
#include<vector>
#include<utility>

/* Class with functionality for a user player (human) to play their role as a player */
class BattleUserPlayer : public IBattlePlayerRole
{
    public:
        /* All of the necessary actions are carried out for the player's turn to be completed */
        std::pair<int,int> takeTurn() override;
        
        /* Deals with placing a ship on the player's grid */ 
        std::vector<std::pair<int,int>> placeShip(int size) override;
};
#endif