#ifndef BATTLE_H
#define BATTLE_H

#include <utility> // std::pair from this header is used to pass grid locations around - https://en.cppreference.com/w/cpp/utility/pair
#include "player.h"
#include "battleUserPlayer.h"

/* This class acts as an interface class for different types of battles */
/* All classes derived from the class must provide this functionality */
/* The functionality declared in this "interface" class will ensure a battleships game can be played whether that be between humans, human and computer or computers */
class Battle
{  
    public:        
        /* To be overriden and implemented by subclass - Return bool whether game is finished */
        /* Returns true if game is over, false if the game is still to be play*/
        virtual bool isGameOver() = 0;
        
        /* To be overriden and implemented by subclass - Method to update the Grids and corresponding Ships after a location has been choosen for a player's turn */
        /* Returns - true if the player hit an enemy ship, false if not */
        virtual bool updateGridsAndShips(const std::pair<int,int> &gridLocationToUpdate, const Player &player, const Player &enemyPlayer) = 0;
        
        /* To be overriden and implemented by subclass - To be overriden and implemented by subclass - Method which controls turns */
        virtual void play() = 0;
        
        /* To be overriden and implemented by subclass - Method which controls placing ships at start by 2 players */
        virtual void placeShips() = 0;
};
#endif