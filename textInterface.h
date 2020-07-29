#ifndef TEXTINTERFACE_H
#define TEXTINTERFACE_H

#include "grid.h"

class TextInterface
{
    private:         
        // Constructor is private 
        TextInterface();        
    
    public:    
        /* Show the a grid on the screen */
        /* @grid is passed as a const reference to stop copying */
        static void display(const Grid& grid);
        
        /* Show text on the screen */
        /* @text is passed as a const reference to stop copying */
        static void display(const std::string& text);
        
        /* Show integer on the screen */
        /* @number is passed as a const reference to stop copying */
        static void display(const int& number);
        
        /* Ask user for input with a message */
        /* Returns the user's response */
        /* @inputMessage is passed as a const reference to stop copying */
        static int receiveIntInput(const std::string& inputMessage);
        
};
#endif