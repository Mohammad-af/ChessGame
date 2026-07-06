#include "Move.hpp"

Move::Move(int from_row, int from_col, int to_row, int to_col) : fromRow(from_row), fromCol(from_col), toRow(to_row), toCol(to_col) {}

int Move::GetFromRow() const { return fromRow; }

int Move::GetFromCol() const { return fromCol; }

int Move::GetToRow() const { return toRow; }

int Move::GetToCol() const { return toCol; }

void Move::SetCapturedPiece(std::unique_ptr<Piece> &&piece) { capturedPiece = std::move(piece); }

std::unique_ptr<Piece> Move::ReleaseCapturedPiece() { return std::move(capturedPiece); }