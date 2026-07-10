#ifndef BOARD_HPP
#define BOARD_HPP

#include <memory>
#include <string>
#include "Piece.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"
#include "Move.hpp"

class Board
{
private:
    std::unique_ptr<Piece> grid[8][8];
    int whiteKingRow;
    int whiteKingCol;
    int blackKingRow;
    int blackKingCol;

public:
    void Setup();
    Piece *GetPiece(int, int) const;
    bool IsEmpty(int, int) const;
    void ApplyMove(Move &);
    void UndoMove(Move &);
    int GetKingRow(Piece::Color) const;
    int GetKingCol(Piece::Color) const;
    bool IsPathClear(const Move &, Piece *);
    bool IsSquareAttacked(int, int, Piece::Color);
    bool IsMoveLegal(Move &, Piece::Color);
    bool HasLegalMove(Piece::Color);
};

#endif