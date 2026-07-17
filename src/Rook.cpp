#include "Rook.hpp"
#include "Move.hpp"

Rook::Rook(Color color) : Piece(color) {}

bool Rook::IsValidMove(const Move &move) const { return move.GetFromRow() - move.GetToRow() == 0 || move.GetFromCol() - move.GetToCol() == 0; }

bool Rook::AttacksSquare(const Move &move) const { return IsValidMove(move); }

std::string Rook::GetSymbol() const
{
    if (GetColor() == Color::White)
        return u8"♖";
    else
        return u8"♜";
}

Piece::Type Rook::GetType() const { return Type::Rook; }