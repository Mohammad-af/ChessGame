#include "Queen.hpp"
#include <cmath>
#include "Move.hpp"

Queen::Queen(Color color) : Piece(color) {}

bool Queen::IsValidMove(const Move &move) const
{
    if (abs(move.GetFromRow() - move.GetToRow()) == abs(move.GetFromCol() - move.GetToCol()))
        return true;
    if (move.GetFromRow() - move.GetToRow() == 0 || move.GetFromCol() - move.GetToCol() == 0)
        return true;
    return false;
}

bool Queen::AttacksSquare(const Move &move) const { return IsValidMove(move); }

std::string Queen::GetSymbol() const
{
    if (GetColor() == Color::White)
        return u8"♕";
    else
        return u8"♛";
}

Piece::PieceType Queen::GetType() const { return PieceType::Queen; }