#include "../include/Rook.hpp"

Rook::Rook(Piece::Color color) : Piece(color) {}

bool Rook::IsValidMove(int row1, int row2, int col1, int col2) const
{
    if (row1 - row2 == 0 || col1 - col2 == 0)
        return true;
    return false;
}

char Rook::GetSymbol() const { return 'R'; }

Piece::PieceType Rook::GetType() const { return PieceType::Rook; }