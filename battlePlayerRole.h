#ifndef BATTLEUSERPLAYER_H
#define BATTLEUSERPLAYER_H

#include "iBattlePlayerRole.h"

/* Class with functionality for a user player (human) to play their role as a player */
class BattleUserPlayer : public IBattleUserPlayer
{
    public:
        /* All of the necessary actions are carried out for the player's turn to be completed */
        GridLocation takeTurn();
        
        /* Deals with placing a ship on the player's grid */ 
        void placeShip(int size);
};
#endif