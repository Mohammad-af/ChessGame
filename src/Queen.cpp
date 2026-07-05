#include "Queen.hpp"
#include <cmath>

Queen::Queen(Color color) : Piece(color) {}

bool Queen::IsValidMove(int row1, int col1, int row2, int col2) const
{
    if (abs(row1 - row2) == abs(col1 - col2))
        return true;
    if (row1 - row2 == 0 || col1 - col2 == 0)
        return true;
    return false;
}

bool Queen::AttacksSquare(int row1, int col1, int row2, int col2) const { return IsValidMove(row1, col1, row2, col2); }

std::string Queen::GetSymbol() const
{
    if (GetColor() == Color::White)
        return u8"♕";
    else
        return u8"♛";
}

Piece::PieceType Queen::GetType() const { return PieceType::Queen; }