#include <iostream>
#include <string>
#include "include/Dispaly.hpp"
#include "include/Game.hpp"
#include "include/Console.hpp"

int main()
{
    SetupConsole();
    bool run_game = true;
    std::string user_move;
    Game game;
    game.Setup();
    while (run_game)
    {
        ClearConsole();
        game.Draw();
        user_move = game.UserInput();
        if (game.ValidateMove(user_move))
            game.GameState();
        PauseConsole();
    }
    return 0;
}