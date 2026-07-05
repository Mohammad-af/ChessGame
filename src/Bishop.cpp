#include "Bishop.hpp"
#include <cmath>

Bishop::Bishop(Color color) : Piece(color) {}

bool Bishop::IsValidMove(int row1, int col1, int row2, int col2) const
{
    if (abs(row1 - row2) == abs(col1 - col2))
        return true;
    return false;
}

bool Bishop::AttacksSquare(int row1, int col1, int row2, int col2) const { return IsValidMove(row1, col1, row2, col2); }

std::string Bishop::GetSymbol() const
{
    if (GetColor() == Color::White)
        return u8"♗";
    else
        return u8"♝";
}

Piece::PieceType Bishop::GetType() const { return PieceType::Bishop; }