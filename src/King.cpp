#include "King.hpp"
#include <cmath>
#include "Move.hpp"

King::King(Color color) : Piece(color) {}

bool King::IsValidMove(const Move &move) const
{
    if ((std::abs(move.GetFromRow() - move.GetToRow()) <= 1 && std::abs(move.GetFromCol() - move.GetToCol()) <= 1) || (move.GetFromRow() - move.GetToRow() == 0 && std::abs(move.GetFromCol() - move.GetToCol()) == 2))
        return true; // The secend condition happens when we castle.
    return false;
}

bool King::AttacksSquare(const Move &move) const { return IsValidMove(move); }

std::string King::GetSymbol() const
{
    if (GetColor() == Color::White)
        return u8"♔";
    else
        return u8"♚";
}

Piece::PieceType King::GetType() const { return PieceType::King; }