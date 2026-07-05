#include "King.hpp"
#include <cmath>

King::King(Color color) : Piece(color) {}

bool King::IsValidMove(int row1, int col1, int row2, int col2) const
{
    if ((abs(row1 - row2) <= 1 && abs(col1 - col2) <= 1) || (row1 - row2 == 0 && abs(col1 - col2) == 2)) // The secend condition happens when we castle.
        return true;
    return false;
}

bool King::AttacksSquare(int row1, int col1, int row2, int col2) const { return IsValidMove(row1, col1, row2, col2); }

std::string King::GetSymbol() const
{
    if (GetColor() == Color::White)
        return u8"♔";
    else
        return u8"♚";
}

Piece::PieceType King::GetType() const { return PieceType::King; }