#include "../include/Bishop.hpp"
#include <cmath>

Bishop::Bishop(Piece::Color color) : Piece(color) {}

bool Bishop::IsValidMove(int row1, int row2, int col1, int col2) const
{
    if (abs(row1 - row2) == abs(col1 - col2))
        return true;
    return false;
}

char Bishop::GetSymbol() const { return 'B'; }