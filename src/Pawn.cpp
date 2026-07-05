#include "Pawn.hpp"
#include <cmath>

Pawn::Pawn(Color color) : Piece(color) {}

bool Pawn::IsValidMove(int row1, int col1, int row2, int col2) const
{
    if (GetColor() == Color::White && ((row1 - row2 == 1 && col1 - col2 == 0) || (row1 - row2 == 2 && col1 - col2 == 0 && IsFirstMove()) || (row1 - row2 == 1 && abs(col1 - col2) == 1)))
        return true;
    if (GetColor() == Color::Black && ((row1 - row2 == -1 && col1 - col2 == 0) || (row1 - row2 == -2 && col1 - col2 == 0 && IsFirstMove()) || (row1 - row2 == -1 && abs(col1 - col2) == 1)))
        return true;
    return false;
}

bool Pawn::AttacksSquare(int row1, int col1, int row2, int col2) const
{
    if (GetColor() == Color::White && row1 - row2 == 1 && abs(col1 - col2) == 1)
        return true;
    if (GetColor() == Color::Black && row1 - row2 == -1 && abs(col1 - col2) == 1)
        return true;
    return false;
}

std::string Pawn::GetSymbol() const
{
    if (GetColor() == Color::White)
        return u8"♙";
    else
        return u8"♟";
}

Piece::PieceType Pawn::GetType() const { return PieceType::Pawn; }