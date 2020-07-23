#ifndef BATTLE_H
#define BATTLE_H

#include <utility> // std::pair from this header is used to pass grid locations
#include "player.h"

class Battle
{
    private:        
        // Player 1
        std::shared_ptr<Player> player1;
        
        // Player 2
        std::shared_ptr<Player> player2;
        
    public:
        /* Constructor */
        Battle(bool p1IsAUser, bool p2IsAUser);      
    
        // Return bool whether game is finished
        bool isGameOver();
        
        /* Method to update the Grids after a location has been choosen for a player's turn */
        void updateGrids(std::pair<int,int> gridLocationToUpdate, const Player& player, const Player& enemyPlayer);
        
        /* Method to update hit locations of enemy ships after a location has been choosen for a player's turn */
        void updateGrids(std::pair<int,int> gridLocationToShootAt, const Player& enemyPlayer);
        
        /* Method which controls turns */
        void play();
};
#endif