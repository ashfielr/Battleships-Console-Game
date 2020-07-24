#ifndef PLAYERVSPLAYER_H
#define PLAYERVSPLAYER_H

#include "battle.h"

class PlayerVsPlayer : public Battle
{  
    private:
        BattleUserPlayer player1;
        BattleUserPlayer player2;

    public:  
        // Constructor
        PlayerVsPlayer();
    
        // Return bool whether game is finished
        bool isGameOver() override;
        
        /* Method to update the Grids and Ships after a location has been choosen for a player's turn */
        void updateGridsAndShips(const std::pair<int,int> &gridLocationToUpdate, const Player& player, const Player& enemyPlayer) override;     
        
        /* Method which controls turns */
        void play() override;
        
        /* Method which controls placing ships at start */
        void placeShips() override;
};
#endif