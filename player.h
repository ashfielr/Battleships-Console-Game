#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "grid.h" // Grid library
#include "ship.h" // Ship library
#include "iBattlePlayerRole.h" 

class Player
{
    private:        
        // The player name
        std::string name;
        
        // The Ships that the user owns
        std::vector<Ship> ships;
        
        // The player's own grid on which their ships are located and status from enemy shots are displayed
        Grid playerGrid;
        
        // The enemy player's grid which does not show the ship locations but shows the status from the players shots
        Grid enemyGrid;
        
        // Collection of the locations on the grid the player has already used a turn to shoot at
        std::vector<std::pair<int,int>> gridLocationsShotAt;
        
        // The role the player will play - the player will either play the role of a user or a computer
        IBattlePlayerRole* role;
        
        // Friend function in class that implements IBattlePlayerRole class that will access the player's ships
        friend void addToEndingLocationsIfValid(Player* playerPtr, std::pair<int,int>& startLocation, int valueChanged, char columnOrRowChanged, std::vector<std::pair<int,int>>& availableEndLocations, int size);
    
    public:
        /* Constructor */
        Player(std::string _name, bool isAUser);
        
        /* Destructor - free up memory */
        ~Player();
    
        /* Returns the player's name */
        std::string getName();
        
        /* Allows the player's name to be changed */
        void setName(std::string _name);
};
#endif