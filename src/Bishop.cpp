#include "../include/Bishop.hpp"
Bishop::Bishop(Piece::Color color) : Piece(color) {}
bool Bishop::IsValidMove(int row1, int col1, int row2, int col2) const
{
    return true;
}
char Bishop::GetSymbol() const
{
    return 'B';
}