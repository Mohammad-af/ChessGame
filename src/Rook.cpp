#include "Rook.hpp"

Rook::Rook(Color color) : Piece(color) {}

bool Rook::IsValidMove(int row1, int col1, int row2, int col2) const
{
    if (row1 - row2 == 0 || col1 - col2 == 0)
        return true;
    return false;
}

bool Rook::AttacksSquare(int row1, int col1, int row2, int col2) const { return IsValidMove(row1, col1, row2, col2); }

std::string Rook::GetSymbol() const
{
    if (GetColor() == Color::White)
        return u8"♖";
    else
        return u8"♜";
}

Piece::PieceType Rook::GetType() const { return PieceType::Rook; }