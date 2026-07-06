#include "Bishop.hpp"
#include <cmath>

Bishop::Bishop(Color color) : Piece(color) {}

bool Bishop::IsValidMove(const Move &move) const
{
    if (abs(move.GetFromRow() - move.GetToRow()) == abs(move.GetFromCol() - move.GetToCol()))
        return true;
    return false;
}

bool Bishop::AttacksSquare(const Move &move) const { return IsValidMove(move); }

std::string Bishop::GetSymbol() const
{
    if (GetColor() == Color::White)
        return u8"♗";
    else
        return u8"♝";
}

Piece::PieceType Bishop::GetType() const { return PieceType::Bishop; }