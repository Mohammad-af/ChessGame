#include "../include/Pawn.hpp"
Pawn::Pawn(Color color) : Piece(color) {}
bool Pawn::IsValidMove(int row1, int col1, int row2, int col2) const
{
    return true;
}
char Pawn::GetSymbol() const
{
    return 'P';
}