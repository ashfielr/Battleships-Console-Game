#ifndef BATTLEUSERPLAYER_H
#define BATTLEUSERPLAYER_H

#include<vector> // Im using std::vector here
#include<utility> // Im using std::pair here

#include "player.h"

/* Class with functionality for a user player (human) to play their role as a player */
class BattleUserPlayer : public Player
{
    public:
        /* Constructor */
        BattleUserPlayer();
    
        /* All of the necessary actions are carried out for the player's turn to be completed */
        /* Returns the location they have chosen to fire at on the enemy's grid */
        std::pair<int,int> takeTurn();
        
        /* Deals with placing a ship on the player's grid */ 
        /* Returns collection of locations which belong to the ship being placed */
        std::vector<std::pair<int,int>> placeShip(int size);
};
#endif