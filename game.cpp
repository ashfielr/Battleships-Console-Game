#include "playerVsPlayer.h"
#include "textInterface.h"

#include <string>
#include <iostream>

int main()
{  
    bool gameRunning = true;
    
    while(gameRunning)
    {
        std::string menuMessage = "Welcome to Battleships!\nDo you wish to:\n0: Play\n1: Read the instructions\n2: Exit\n";
        int menuSelection = TextInterface::receiveIntInput(menuMessage); // Will request integer input for message
        
        bool validOptionSelected = true;
        if(menuSelection != 0 && menuSelection != 1 && menuSelection != 2)
        {
            TextInterface::display("Please enter a valid option.");
            validOptionSelected = false;
        }
        
        if(validOptionSelected)
        {
            switch(menuSelection)
            {
                // Play the game
                case 0:
                {
                    PlayerVsPlayer battle;
                    battle.placeShips();
                    while(!battle.isGameOver())  
                    {
                        battle.play();
                    }
                    break;
                }

                // Display the game instructions
                case 1:
                {
                    std::string instructions = "INSTRUCTIONS\nThis is the section where the user will be told how to play the game...\n";
                    TextInterface::display(instructions);
                    break;
                }

                // Exit the game
                case 2: 
                {
                    gameRunning = false;
                    break;
                }
            }
        }
        
    }
     
    return 0;  
}