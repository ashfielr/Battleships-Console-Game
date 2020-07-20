#ifndef IBATTLEPLAYERROLE_H
#define IBATTLEPLAYERROLE_H

#include<utility> // for std::pair
#include<vector>

/* Interface class which will ensure any class that inherits from it will implement the methods */
class IBattlePlayerRole
{           
    public:
        /* All of the necessary actions are carried out for the player's turn to be completed */
        virtual std::pair<int,int> takeTurn() = 0; // https://en.cppreference.com/w/cpp/utility/pair/pair
        
        /* Deals with placing a ship on the player's grid */ 
        virtual std::vector<std::pair<int,int>> placeShip(int size) = 0;
};
#endif