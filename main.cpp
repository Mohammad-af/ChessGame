#include <iostream>
#include <string>
#include "include/Dispaly.hpp"
#include "include/Game.hpp"
using namespace std;
int main()
{
    bool run_game = true;
    string user_move;
    Game game;
    game.Setup();
    while (run_game)
    {
        system("cls");
        game.Draw();
        user_move = game.UserInput();
        if (game.ValidateMove(user_move))
            game.GameState();
        system("pause");
    }
    return 0;
}