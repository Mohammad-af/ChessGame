#include "../include/Knight.hpp"

Knight::Knight(Piece::Color color) : Piece(color) {}

bool Knight::IsValidMove(int row1, int row2, int col1, int col2) const
{
    return true;
}

char Knight::GetSymbol() const { return 'N'; }