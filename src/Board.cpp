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

Piece *Board::GetPiece(int row, int col) const { return Grid[row][col].get(); }

bool Board::IsEmpty(int row, int col) const
{
    if (Grid[row][col] == nullptr)
        return true;
    return false;
}

bool Board::MovePiece(int row1, int row2, int col1, int col2)
{
    Grid[row2][col2] = move(Grid[row1][col1]);
    cout << "Successful move.\n";
    return true;
}