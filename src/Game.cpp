#include "Game.hpp"
#include <iostream>

int Game::Turn = 1;

std::string Game::UserInput() const
{
    std::string user_move;
    do
    {
        if (TurnColor() == Piece::Color::White)
            std::cout << "\nWhite move: ";
        else
            std::cout << "\nBlack move: ";
        std::cin >> user_move;
        if (user_move.length() != 4)
            std::cout << "INVALID INPUT FORMAT! Use this format: a2a3\n";
    } while (user_move.length() != 4);
    return user_move;
}

bool Game::ValidateMove(const std::string &user_move)
{
    int col1, col2, row1, row2;
    if (user_move[0] >= 97)        // 'a' = 97 , 'b' = 98 , ...
        col1 = user_move[0] - 'a'; // example: user_move[0] = 'b' = 98(ASCII); int col1 = 98 - 97 = 1; Grid[][col1] is the second column from left.
    else                           // 'A' = 65 , 'b' = 66 , ...
        col1 = user_move[0] - 'A';
    if (user_move[2] >= 97)
        col2 = user_move[2] - 'a';
    else
        col2 = user_move[2] - 'A';
    row1 = 7 - (user_move[1] - '1'); // example: user_move[1] = '2' = 50(ASCII); row1 = 7 - (50 - 49) = 6; Grid[row1][] is the second row from bottom.
    row2 = 7 - (user_move[3] - '1');
    if (row1 < 0 || row1 >= 8 || row2 < 0 || row2 >= 8 || col1 < 0 || col1 >= 8 || col2 < 0 || col2 >= 8)
    {
        std::cout << "INVALID MOVE! Enter coloumn a-h and row 1-8.\n";
        return false;
    }
    if (board.GetPiece(row1, col1) == nullptr)
    {
        std::cout << "INVALID MOVE! The starting point has no pieces in it.\n";
        return false;
    }
    if (board.GetPiece(row1, col1)->GetColor() != TurnColor())
    {
        std::cout << "INVALID MOVE! You cannot move the opponent's piece.\n";
        return false;
    }
    if (row1 == row2 && col1 == col2)
    {
        std::cout << "INVALID MOVE! You cannot move to the same place.\n";
        return false;
    }
    Piece *piece = board.GetPiece(row1, col1);
    if (!(piece->IsValidMove(row1, row2, col1, col2)))
    {
        std::cout << "INVALID MOVE! This piece cannot move like this.\n";
        return false;
    }
    if (!(board.IsPathClear(row1, row2, col1, col2, piece)))
    {
        std::cout << "INVALID MOVE! The path is not clear.\n";
        return false;
    }
    board.MovePiece(row1, row2, col1, col2);
    Turn++;
    return true;
}

void Game::GameState()
{
    bool check = IsSquareAttacked(board.GetKingRow(TurnColor()), board.GetKingCol(TurnColor()), TurnColor());
}

bool Game::IsSquareAttacked(int row, int col, Piece::Color turn_color) const
{
    return false;
}

Piece::Color Game::TurnColor() const
{
    if (Turn % 2 == 1)
        return Piece::Color::White;
    else
        return Piece::Color::Black;
}

void Game::Setup() { board.Setup(); }
void Game::Draw() const { Display::Draw(Game::board); }