#include "textInterface.h"

#include <iostream>

/* Show the a grid on the screen */
void TextInterface::display(const std::shared_ptr<Grid> &gridToDisplay)
{
    std::cout << "[   ] | [ 0 ] [ 1 ] [ 2 ] [ 3 ] [ 4 ] [ 5 ] [ 6 ] [ 7 ] [ 8 ] [ 9 ]" << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;
    for(int row=0; row<10; row++)
    {
        std::cout << "[ " << row << " ] |";
        
        for(int col=0; col<10; col++)
        {
            std::cout << " [ " << gridToDisplay->getGrid()[row][col] << " ]";
        }
        std::cout << std::endl;
    }
}

/* Show text on the screen */
void TextInterface::display(const std::string& text)
{
    std::cout << text << std::endl;
}

/* Show a number on the screen */
void TextInterface::display(const int& number)
{
    std::cout << number << std::endl;
}

/* Ask user for input with a message */
/* Returns int - the user's response as required datatype specified by @returnType parameter */
int TextInterface::receiveIntInput(const std::string& inputMessage)
{
    std::cout << inputMessage;
    int inputFromUser;
    std::cin >> inputFromUser;
    return inputFromUser;
}

/* Ask user for input with a message */
/* Returns char - the user's response as required datatype specified by @returnType parameter */
char TextInterface::receiveCharInput(const std::string& inputMessage)
{
    std::cout << inputMessage;
    char inputFromUser;
    std::cin >> inputFromUser;
    return inputFromUser;
}