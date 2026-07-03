#include "../include/Piece.hpp"
Piece::Piece(Color color) : PieceColor(color) {}
Piece::Color Piece::GetColor() const
{
    return PieceColor;
}