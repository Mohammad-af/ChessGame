#include "../include/Pawn.hpp"
#include <cmath>

Pawn::Pawn(Color color) : Piece(color) {}

bool Pawn::IsValidMove(int row1, int row2, int col1, int col2) const
{
    if ((abs(row1 - row2) <= 2 && col1 - col2 == 0) || (abs(row1 - row2) == 1 && abs(col1 - col2) == 1)) // In the first condition abs(row1 - row2) != 0 because the pawn moves to the same place, which is prevented in the ValidateMove function.
        return true;
    return false;
}

char Pawn::GetSymbol() const { return 'P'; }

Piece::PieceType Pawn::GetType() const { return PieceType::Pawn; }