#include "Knight.hpp"
#include <cmath>

Knight::Knight(Color color) : Piece(color) {}

bool Knight::IsValidMove(int row1, int col1, int row2, int col2) const
{
    if ((abs(row1 - row2) == 2 && abs(col1 - col2) == 1) || (abs(row1 - row2) == 1 && abs(col1 - col2) == 2))
        return true;
    return false;
}

bool Knight::AttacksSquare(int row1, int col1, int row2, int col2) const { return IsValidMove(row1, col1, row2, col2); }

std::string Knight::GetSymbol() const
{
    if (GetColor() == Color::White)
        return u8"♘";
    else
        return u8"♞";
}

Piece::PieceType Knight::GetType() const { return PieceType::Knight; }