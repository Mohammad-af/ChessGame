#include "../include/Rook.hpp"

Rook::Rook(Piece::Color color) : Piece(color) {}

bool Rook::IsValidMove(int row1, int row2, int col1, int col2) const
{
    return true;
}

char Rook::GetSymbol() const { return 'R'; }