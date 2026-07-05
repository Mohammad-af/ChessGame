#include "Piece.hpp"

Piece::Piece(Color color) : PieceColor(color) {}

Piece::Color Piece::GetColor() const { return PieceColor; }

bool Piece::IsFirstMove() const { return FirstMove; }

void Piece::MadeFisrtMove() { FirstMove = false; }