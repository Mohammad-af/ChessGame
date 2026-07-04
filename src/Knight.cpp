#include "../include/Knight.hpp"
#include <cmath>

Knight::Knight(Piece::Color color) : Piece(color) {}

bool Knight::IsValidMove(int row1, int row2, int col1, int col2) const
{
    if ((abs(row1 - row2) == 2 && abs(col1 - col2) == 1) || (abs(row1 - row2) == 1 && abs(col1 - col2) == 2))
        return true;
    return false;
}

char Knight::GetSymbol() const { return 'N'; }