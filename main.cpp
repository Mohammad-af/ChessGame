#include <iostream>
#include <string>
#include <fstream>
#include <filesystem> // For deleting previous games.
#include <limits>     // For cin.ignore().
#include "include/Dispaly.hpp"
#include "include/Game.hpp"
#include "include/Console.hpp"

int main()
{
    SetupConsole();
    bool run_game = true;
    Game game;
    int option;
    std::ifstream file("save.txt");
    if (file)
    {
        while (true)
        {
            ClearConsole();
            std::cout << "Choose an option(Enter 1 or 2 or 3):\n 1. Load Last Game\n 2. New Game\n 3. Exit\n";
            if (std::cin >> option && option >= 1 && option <= 3) // "std::cin >> option" Reads the input and checks whether it is a valid integer.
                break;
            std::cout << "Invalid option.\n";
            std::cin.clear();                                                   // Clears the error if user used an invalid input like 'a'.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clears the buffer.
        }
        switch (option)
        {
        case 1:
            game.LoadGame("save.txt");
            break;
        case 2:
            break;
        case 3:
            run_game = false;
            break;
        }
    }
    while (run_game)
    {
        ClearConsole();
        game.Draw();
        Move move(0, 0, 0, 0);
        if (!game.UserInput(move))
        {
            run_game = false;
            break;
        }
        if (game.ValidateMove(move))
        {
            ClearConsole();
            game.Draw();
            switch (game.GameState())
            {
            case Game::Status::Play:
                break;
            case Game::Status::Check:
                std::cout << "IT'S CHECK! The " << game.GetColorName(game.GetTurnColor()) << " King is on check.\n\n";
                break;
            case Game::Status::Checkmate:
                std::cout << "IT'S CHECKMATE! " << game.GetColorName(game.GetOpponentColor()) << " WON.\n\n";
                run_game = false;
                break;
            case Game::Status::Stalemate:
                std::cout << "IT'S A DRAW! It's stalemate!\n\n";
                run_game = false;
                break;
            case Game::Status::ThreefoldRepetition:
                std::cout << "IT'S A DRAW! The same position has occurred three times.\n\n";
                run_game = false;
                break;
            case Game::Status::InsufficientMaterial:
                std::cout << "IT'S A DRAW! There is insufficient material to checkmate.\n\n";
                run_game = false;
                break;
            case Game::Status::FiftyMoveRule:
                std::cout << "IT'S A DRAW! Fifty consecutive moves were made without a pawn move or capture.\n\n";
                run_game = false;
                break;
            }
        }
        PauseConsole();
    }
    return 0;
}