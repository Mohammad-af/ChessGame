#include "Rook.hpp"
#include "Move.hpp"

Rook::Rook(Color color) : Piece(color) {}

bool Rook::IsValidMove(const Move &move) const
{
    if (move.GetFromRow() - move.GetToRow() == 0 || move.GetFromCol() - move.GetToCol() == 0)
        return true;
    return false;
}

bool Rook::AttacksSquare(const Move &move) const { return IsValidMove(move); }

std::string Rook::GetSymbol() const
{
    if (GetColor() == Color::White)
        return u8"♖";
    else
        return u8"♜";
}

Piece::PieceType Rook::GetType() const { return PieceType::Rook; }