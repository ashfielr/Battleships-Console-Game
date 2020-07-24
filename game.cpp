#include "playerVsPlayer.h"
#include <iostream>

int main()
{
    PlayerVsPlayer battle;
    battle.placeShips();
    while(!battle.isGameOver())  
    {
        battle.play();
    }
    return 0;
}