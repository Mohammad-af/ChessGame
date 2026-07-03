#include "../include/Game.hpp"
#include <iostream>
using namespace std;
int Game::Turn = 1;
string Game::UserInput()
{
    string user_move;
    if (Turn % 2 == 1)
        cout << "\nWhite move: ";
    else
        cout << "\nBlack move: ";
    do
    {
        cin >> user_move;
        if (user_move.length() != 4)
            cout << "Invalid INPUT FORMAT! Use this format: a2a3\n";
    } while (user_move.length() != 4);
    return user_move;
}
bool Game::ValidateMove()
{
    Turn++;
    return true;
}
void Game::GameState()
{
}