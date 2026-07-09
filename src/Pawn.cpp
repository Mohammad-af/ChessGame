#include "Pawn.hpp"
#include <cmath>
#include "Move.hpp"

Pawn::Pawn(Color color) : Piece(color) {}

bool Pawn::IsValidMove(const Move &move) const
{
    if (GetColor() == Color::White && ((move.GetFromRow() - move.GetToRow() == 1 && move.GetFromCol() - move.GetToCol() == 0) || (move.GetFromRow() - move.GetToRow() == 2 && move.GetFromCol() - move.GetToCol() == 0 && IsFirstMove()) || (move.GetFromRow() - move.GetToRow() == 1 && std::abs(move.GetFromCol() - move.GetToCol()) == 1)))
        return true;
    if (GetColor() == Color::Black && ((move.GetFromRow() - move.GetToRow() == -1 && move.GetFromCol() - move.GetToCol() == 0) || (move.GetFromRow() - move.GetToRow() == -2 && move.GetFromCol() - move.GetToCol() == 0 && IsFirstMove()) || (move.GetFromRow() - move.GetToRow() == -1 && std::abs(move.GetFromCol() - move.GetToCol()) == 1)))
        return true;
    return false;
}

bool Pawn::AttacksSquare(const Move &move) const
{
    if (GetColor() == Color::White && move.GetFromRow() - move.GetToRow() == 1 && std::abs(move.GetFromCol() - move.GetToCol()) == 1)
        return true;
    if (GetColor() == Color::Black && move.GetFromRow() - move.GetToRow() == -1 && std::abs(move.GetFromCol() - move.GetToCol()) == 1)
        return true;
    return false;
}

std::string Pawn::GetSymbol() const
{
    if (GetColor() == Color::White)
        return u8"♙";
    else
        return u8"♟";
}

Piece::PieceType Pawn::GetType() const { return PieceType::Pawn; }