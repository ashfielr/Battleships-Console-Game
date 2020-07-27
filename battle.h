#ifndef BATTLE_H
#define BATTLE_H

#include <utility> // std::pair from this header is used to pass grid locations
#include "player.h"
#include "battleUserPlayer.h"

class Battle
{  
    public:        
        // To be overriden by subclass - Return bool whether game is finished
        virtual bool isGameOver() = 0;
        
        /* To be overriden by subclass - Method to update the Grids after a location has been choosen for a player's turn */
        /* Returns - true if the player hit an enemy ship, false if not */
        virtual bool updateGridsAndShips(const std::pair<int,int> &gridLocationToUpdate, const Player &player, const Player &enemyPlayer) = 0;
        
        /* To be overriden by subclass - Method which controls turns */
        virtual void play() = 0;
        
        /* Method which controls placing ships at start */
        virtual void placeShips() = 0;
};
#endif