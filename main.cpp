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
            case Game::Status::InsufficientMaterial:
                std::cout << "IT'S A DRAW! There is insufficient material to checkmate.\n\n";
                run_game = false;
                break;
            case Game::Status::FiftyMoveRule:
                std::cout << "IT'S A DRAW! Fifty consecutive moves were made without a pawn move or capture.\n\n";
                run_game = false;
                break;
            case Game::Status::Checkmate:
                std::cout << "IT'S CHECKMATE! " << game.GetColorName(game.GetOpponentColor()) << " WON.\n\n";
                run_game = false;
                break;
            case Game::Status::Check:
                std::cout << "IT'S CHECK! The " << game.GetColorName(game.GetTurnColor()) << " King is on check.\n\n";
                break;
            case Game::Status::Stalemate:
                std::cout << "IT'S STALEMATE! It's a DRAW.\n\n";
                run_game = false;
                break;
            default:
                break;
            }
        }
        PauseConsole();
    }
    return 0;
}