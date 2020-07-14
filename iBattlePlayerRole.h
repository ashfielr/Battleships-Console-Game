#ifndef IBATTLEPLAYERROLE_H
#define IBATTLEPLAYERROLE_H

#include "gridLocation.h"

/* Interface class which will ensure any class that inherits from it will implement the methods */
class IBattlePlayerRole
{           
    public:
        /* All of the necessary actions are carried out for the player's turn to be completed */
        virtual GridLocation takeTurn() = 0;
        
        /* Deals with placing a ship on the player's grid */ 
        virtual void placeShip(int size) = 0;
};
#endif