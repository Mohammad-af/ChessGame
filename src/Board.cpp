#include "../include/Board.hpp"
#include <iostream>
using namespace std;
void Board::Setup()
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (row > 1 && row < 6)
                Grid[row][col] = nullptr;
            else if (row == 1)
                Grid[row][col] = make_unique<Pawn>(Piece::Color::BLACK);
            else if (row == 6)
                Grid[row][col] = make_unique<Pawn>(Piece::Color::WHITE);
            else if (row == 0)
            {
                if (col == 0 || col == 7)
                    Grid[row][col] = make_unique<Rook>(Piece::Color::BLACK);
                else if (col == 1 || col == 6)
                    Grid[row][col] = make_unique<Knight>(Piece::Color::BLACK);
                else if (col == 2 || col == 5)
                    Grid[row][col] = make_unique<Bishop>(Piece::Color::BLACK);
                else if (col == 3)
                    Grid[row][col] = make_unique<Queen>(Piece::Color::BLACK);
                else
                    Grid[row][col] = make_unique<King>(Piece::Color::BLACK);
            }
            else
            {
                if (col == 0 || col == 7)
                    Grid[row][col] = make_unique<Rook>(Piece::Color::WHITE);
                else if (col == 1 || col == 6)
                    Grid[row][col] = make_unique<Knight>(Piece::Color::WHITE);
                else if (col == 2 || col == 5)
                    Grid[row][col] = make_unique<Bishop>(Piece::Color::WHITE);
                else if (col == 3)
                    Grid[row][col] = make_unique<Queen>(Piece::Color::WHITE);
                else
                    Grid[row][col] = make_unique<King>(Piece::Color::WHITE);
            }
        }
    }
}
Piece *Board::GetPiece(int row, int col) const
{
    return Grid[row][col].get();
}
bool Board::IsEmpty(int row, int col) const
{
    if (Grid[row][col] == nullptr)
        return true;
    return false;
}
bool Board::MovePiece(char col1, int row1, char col2, int row2)
{
    int column1, column2;
    if (col1 >= 97)           // 'a' = 97 , 'b' = 98 , ...
        column1 = col1 - 'a'; // col1 ASCII - 'a' ASCII -> example: col1 = 'b' = 98; int column1 = 98 - 97 = 1; Grid[][column1] is the second column from left.
    else                      // 'A' = 65 , 'b' = 66 , ...
        column1 = col1 - 'A';
    if (col2 >= 97)
        column2 = col2 - 'a';
    else
        int column2 = col2 - 'A';
    row1 = 7 - (row1 - '1'); // example: before -> row1 = '2' = 50; after -> row1 = 7 - (50 - 49) = 6; Grid[row1][] is the second row from bottom.
    row2 = 7 - (row2 - '1');
    if (row1 < 0 || row1 >= 8 || row2 < 0 || row2 >= 8 || column1 < 0 || column1 >= 8 || column2 < 0 || column2 >= 8)
    {
        cout << "INVALID MOVE!\n";
        return false;
    }
    if (Grid[row1][column1] == nullptr)
    {
        cout << "INVALID MOVE! The starting point has no pieces in it.\n";
        return false;
    }
    Game game;
    if (!game.ValidateMove())
    {
        return false;
        cout << "THIS MOVE IS NOT ALLOWED!";
    }
    Grid[row2][column2] = move(Grid[row1][column1]);
    cout << "Successful move.\n";
    return true;
}