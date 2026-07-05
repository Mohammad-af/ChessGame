#include "Bishop.hpp"
#include <cmath>

Bishop::Bishop(Color color) : Piece(color) {}

bool Bishop::IsValidMove(int row1, int row2, int col1, int col2, Color color) const
{
    if (abs(row1 - row2) == abs(col1 - col2))
        return true;
    return false;
}

std::string Bishop::GetSymbol() const
{
    if (GetColor() == Color::White)
        return u8"♗";
    else
        return u8"♝";
}

Piece::PieceType Bishop::GetType() const { return PieceType::Bishop; }