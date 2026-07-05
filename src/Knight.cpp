#include "Knight.hpp"
#include <cmath>

Knight::Knight(Color color) : Piece(color) {}

bool Knight::IsValidMove(int row1, int row2, int col1, int col2, Color color) const
{
    if ((abs(row1 - row2) == 2 && abs(col1 - col2) == 1) || (abs(row1 - row2) == 1 && abs(col1 - col2) == 2))
        return true;
    return false;
}

std::string Knight::GetSymbol() const
{
    if (GetColor() == Color::White)
        return u8"♘";
    else
        return u8"♞";
}

Piece::PieceType Knight::GetType() const { return PieceType::Knight; }