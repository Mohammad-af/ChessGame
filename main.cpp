#include <iostream>
#include <string>
#include "include/Dispaly.hpp"
#include "include/Game.hpp"
#include "include/Console.hpp"

int main()
{
    SetupConsole();
    bool run_game = true;
    Game game;
    game.Setup();
    while (run_game)
    {
        ClearConsole();
        game.Draw();
        Move move = game.UserInput();
        if (game.ValidateMove(move))
        {
            ClearConsole();
            game.Draw();
            switch (game.GameState())
            {
            case Game::GameStatus::Check:
                std::cout << "IT'S CHECK! The " << game.GetTurnColorName() << " King is on check.\n\n";
                break;
            default:
                break;
            }
        }
        PauseConsole();
    }
    return 0;
}