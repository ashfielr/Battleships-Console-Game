#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "grid.h" // Grid class declaration
#include "ship.h" // Ship class declaration

class Player
{
    // To be inherited by child classes
    protected:        
        // The player name
        std::string name;
        
        // The Ships that the user owns
        std::vector<std::shared_ptr<Ship>> ships;
        
        // The player's own grid on which their ships are located and status from enemy shots are displayed
        std::shared_ptr<Grid> playerGrid;
        
        // The enemy player's grid which does not show the ship locations but shows the status from the players shots
        std::shared_ptr<Grid> enemyGrid;
        
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
        std::vector<std::shared_ptr<Ship>> getShips() const;
        
        /* Adds a ship to the players set of ships */
        void addShip(Ship shipToAdd);
        
        /* Returns the player's grid */
        std::shared_ptr<Grid> getOwnGrid() const;
        
        /* Returns the player's version of enemy grid */
        std::shared_ptr<Grid>  getEnemyGrid() const;
        
        /* Returns the grid locations the player has shot at */
        std::vector<std::pair<int,int>> getGridLocationsShotAt() const;
        
        /* Adds location to the grid locations the player has shot at */
        void addToLocationsShotAt(std::pair<int,int> location);
};
#endif