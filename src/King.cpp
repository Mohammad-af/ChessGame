#include "../include/King.hpp"

King::King(Piece::Color color) : Piece(color) {}

bool King::IsValidMove(int row1, int row2, int col1, int col2) const
{
    return true;
}

char King::GetSymbol() const { return 'K'; }