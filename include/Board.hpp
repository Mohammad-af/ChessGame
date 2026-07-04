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

class Board
{
private:
    std::unique_ptr<Piece> Grid[8][8];
    int WhiteKingRow;
    int WhiteKingCol;
    int BlackKingRow;
    int BlackKingCol;

public:
    void Setup();
    Piece *GetPiece(int, int) const;
    bool IsEmpty(int, int) const;
    bool MovePiece(int, int, int, int);
    int GetKingRow(Piece::Color) const;
    int GetKingCol(Piece::Color) const;
};

#endif