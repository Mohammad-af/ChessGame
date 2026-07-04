#include "../include/Queen.hpp"

Queen::Queen(Piece::Color color) : Piece(color) {}

bool Queen::IsValidMove(int row1, int row2, int col1, int col2) const
{
    return true;
}

char Queen::GetSymbol() const { return 'Q'; }