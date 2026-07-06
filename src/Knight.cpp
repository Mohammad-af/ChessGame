#include "Knight.hpp"
#include <cmath>

Knight::Knight(Color color) : Piece(color) {}

bool Knight::IsValidMove(const Move &move) const
{
    if ((abs(move.GetFromRow() - move.GetToRow()) == 2 && abs(move.GetFromCol() - move.GetToCol()) == 1) || (abs(move.GetFromRow() - move.GetToRow()) == 1 && abs(move.GetFromCol() - move.GetToCol()) == 2))
        return true;
    return false;
}

bool Knight::AttacksSquare(const Move &move) const { return IsValidMove(move); }

std::string Knight::GetSymbol() const
{
    if (GetColor() == Color::White)
        return u8"♘";
    else
        return u8"♞";
}

Piece::PieceType Knight::GetType() const { return PieceType::Knight; }