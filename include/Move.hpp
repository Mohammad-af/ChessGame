#ifndef MOVE_HPP
#define MOVE_HPP

#include <memory>
#include "Piece.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"

class Move
{
private:
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
    std::unique_ptr<Piece> capturedPiece = nullptr;

public:
    Move(int, int, int, int);
    int GetFromRow() const;
    int GetFromCol() const;
    int GetToRow() const;
    int GetToCol() const;
    void SetCapturedPiece(std::unique_ptr<Piece> &&);
    std::unique_ptr<Piece> ReleaseCapturedPiece();
};

#endif