#ifndef TEXTINTERFACE_H
#define TEXTINTERFACE_H

#include "grid.h"

class TextInterface
{
    private: 
        // The singleton instance of thhe class
        std::shared_ptr<TextInterface> instance;
        
        // Constructor is private 
        TextInterface();
        
    
    public:
        /* The Singleton instance of the class */
        std::shared_ptr<TextInterface> getInstance();
    
        /* Show the a grid on the screen */
        void display(Grid grid);
        
        /* Show text on the screen */
        void display(std::string text);
        
        /* Ask user for input with a message */
        /* Returns the user's response */
        std::string receiveInput(std::string inputMessage);
        
};
#endif