#ifndef TEXTINTERFACE_H
#define TEXTINTERFACE_H

#include "grid.h"

#include <memory> // Using smart pointers - std::shared_ptr

/* This is a "static" class - no instances can be created */
/* It provides functionality dealing with inputting and outputting text from/to the console */
class TextInterface
{
    private:         
        // Constructor is private
        TextInterface();        
    
    public:    
        /* Show the a grid on the screen */
        /* @grid is passed as a smart pointer to save memory */
        static void display(const std::shared_ptr<Grid> &gridToDisplay);
        
        /* Show text on the screen */
        /* @text is passed as a const reference to stop copying */
        static void display(const std::string& text);
        
        /* Show integer on the screen */
        /* @number is passed as a const reference to stop copying */
        static void display(const int& number);
        
        /* Ask user for input with a message */
        /* Returns int - the user's response */
        /* @inputMessage is passed as a const reference to stop copying */
        static int receiveIntInput(const std::string& inputMessage);
        
        /* Ask user for input with a message */
        /* Returns char - the user's response */
        /* @inputMessage is passed as a const reference to stop copying */
        static char receiveCharInput(const std::string& inputMessage);      
};
#endif   