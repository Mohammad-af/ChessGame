#include "Knight.hpp"
#include <cmath>
#include "Move.hpp"

Knight::Knight(Color color) : Piece(color) {}

bool Knight::IsValidMove(const Move &move) const { return (std::abs(move.GetFromRow() - move.GetToRow()) == 2 && std::abs(move.GetFromCol() - move.GetToCol()) == 1) || (std::abs(move.GetFromRow() - move.GetToRow()) == 1 && std::abs(move.GetFromCol() - move.GetToCol()) == 2); }

bool Knight::AttacksSquare(const Move &move) const { return IsValidMove(move); }

std::string Knight::GetSymbol() const
{
    if (GetColor() == Color::White)
        return u8"♘";
    else
        return u8"♞";
}

Piece::Type Knight::GetType() const { return Type::Knight; }