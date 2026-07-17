#include "Bishop.hpp"
#include <cmath>
#include "Move.hpp"

Bishop::Bishop(Color color) : Piece(color) {}

bool Bishop::IsValidMove(const Move &move) const { return std::abs(move.GetFromRow() - move.GetToRow()) == std::abs(move.GetFromCol() - move.GetToCol()); }

bool Bishop::AttacksSquare(const Move &move) const { return IsValidMove(move); }

std::string Bishop::GetSymbol() const
{
    if (GetColor() == Color::White)
        return u8"♗";
    else
        return u8"♝";
}

Piece::Type Bishop::GetType() const { return Type::Bishop; }