#include "playerVsPlayer.h"
#include "textInterface.h"

#include <string> // using std::string here

int main()
{  
    bool gameRunning = true;
    
    while(gameRunning)
    {
        std::string menuMessage = "Welcome to Battleships!\nDo you wish to:\n1: Play\n2: Read the instructions\n3: Exit\n";
        int menuSelection = TextInterface::receiveIntInput(menuMessage); // Will request integer input for message
        
        bool validOptionSelected = true;
        if(menuSelection != 1 && menuSelection != 2 && menuSelection != 3)
        {
            TextInterface::display("Please enter a valid option.");
            validOptionSelected = false;
        }
        
        if(validOptionSelected)
        {
            switch(menuSelection)
            {
                // Play the game
                case 1:
                {
                    // Initiate a PVP Battleships game
                    PlayerVsPlayer battle;
                    battle.placeShips();
                    while(!battle.isGameOver())  // Continue to give players turns until all of a player's ships are destroyed
                    {
                        battle.play();
                    }
                    break;
                }

                // Display the game instructions
                case 2:
                {
                    std::string instructions = "INSTRUCTIONS\nThis is the section where the user will be told how to play the game...\n";
                    TextInterface::display(instructions);
                    break;
                }

                // Exit the game
                case 3: 
                {
                    gameRunning = false;
                    break;
                }
            }
        }
        
    }
     
    return 0;  
}