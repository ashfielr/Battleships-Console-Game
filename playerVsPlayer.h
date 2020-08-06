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
        /* Returns - true if ship was hit, false if a ship was not hit */
        bool updateGridsAndShips(const std::pair<int,int> &gridLocationToUpdate, const Player& player, const Player& enemyPlayer) override;     
        
        /* Method deals with an individual player's turn */
        /* Returns - true if the player has won on their turn, otherwise it returns false */
        bool takeTurnForAGivenBattleUserPlayer(BattleUserPlayer &player, int playerNumber, BattleUserPlayer &enemyPlayer);
        
        /* Method which controls turns */
        void play() override;
        
        /* Allows ships to be placed for a given player */
        void placeShipsForAGivenBattleUserPlayer(BattleUserPlayer &player);
        
        /* Method which controls placing ships at start for both players */
        void placeShips() override;
        
        /* Will check if the game has ended after a player's turn and wait until they have confirmed to move onto the next player */
        // Returns true if the game is over, returns false if the game is not over
        bool checkGameOverOrPassTurn(std::string waitForCharMessage);
};
#endif