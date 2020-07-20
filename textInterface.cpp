#include "textInterface.h"

using namespace std;

#include <iostream>

/* The Singleton instance of the class */
std::shared_ptr<TextInterface> TextInterface::getInstance()
{
    if(instance == NULL)
        instance = make_shared<TextInterface>(TextInterface());
    return instance;
}

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
/* Returns the user's response */
std::string TextInterface::receiveInput(const std::string& inputMessage)
{
    cout << inputMessage;
    std::string inputFromUser;
    cin >> inputFromUser;
    return inputFromUser;
}