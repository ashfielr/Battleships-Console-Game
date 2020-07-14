#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "grid.h" // Grid library
#include "ship.h" // Ship library

class Player
{
    private:        
        // The player name
        std::string name;
        
        // The Ships that the user owns
        vector<Ship> ships;
        
        // The player's own grid on which their ships are located and status from enemy shots are displayed
        Grid playerGrid;
        
        // The enemy player's grid which does not show the ship locations but shows the status from the players shots
        Grid enemyGrid;
        
        // Collection of the locations on the grid the player has already used a turn to shoot at
        vector<GridLocation> gridLocationsShotAt;
        
        // BattlePlayerRole role; --> To be implemented
        
    
    public:
        /* Constructor */
        Player(std::string _name);
    
        /* Returns the player's name */
        string getName();
        
        /* Allows the player's name to be changed */
        void setName(std::string _name);
};
#endif