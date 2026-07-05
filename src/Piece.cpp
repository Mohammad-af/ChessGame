#include "Piece.hpp"

Piece::Piece(Color color) : pieceColor(color) {}

Piece::Color Piece::GetColor() const { return pieceColor; }

bool Piece::IsFirstMove() const { return firstMove; }

void Piece::MarkAsMoved() { firstMove = false; }