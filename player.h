#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "grid.h" // Grid library
#include "ship.h" // Ship library

class Player
{
    protected:        
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
         
    public:
        /* Constructors */
        Player();
        Player(std::string _name);       
    
        /* Returns the player's name */
        std::string getName() const;
        
        /* Allows the player's name to be changed */
        void setName(std::string _name);
        
        /* Returns true if all of the player's ships have been destroyed and flase if not */
        bool isAllShipsDestroyed() const;
        
        /* Returns the player's ships */
        std::vector<Ship> getShips() const;
        
        /* Adds a ship to the players set of ships */
        void addShip(Ship shipToAdd);
        
        /* Returns the player's grid */
        Grid getOwnGrid() const;
        
        /* Returns the player's version of enemy grid */
        Grid getEnemyGrid() const;
};
#endif