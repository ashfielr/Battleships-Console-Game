#include "textInterface.h"

using namespace std;

#include <iostream>

/* Show the a grid on the screen */
void TextInterface::display(const Grid& grid)
{
    cout << "[   ] | [ 0 ] [ 1 ] [ 2 ] [ 3 ] [ 4 ] [ 5 ] [ 6 ] [ 7 ] [ 8 ] [ 9 ]" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    for(int row=0; row<10; row++)
    {
        cout << "[ " << row << " ] |";
        
        for(int col=0; col<10; col++)
        {
            cout << " [ " << grid.getGrid()[row][col] << " ]" << endl;
        }
    }
}

/* Show text on the screen */
void TextInterface::display(const std::string& text)
{
    cout << text << endl;
}

/* Ask user for input with a message */
/* Returns the user's response as required datatype specified by @returnType parameter */
template<typename TYPE>
TYPE TextInterface::receiveInput(const std::string& inputMessage, TYPE paramOfTypeToReturn)
{
    cout << inputMessage;
    TYPE inputFromUser;
    cin >> inputFromUser;
    return inputFromUser;
}