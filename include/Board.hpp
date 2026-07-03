#ifndef BOARD_HPP
#define BOARD_HPP

#include <memory>
#include "../include/Piece.hpp"
#include "../include/Pawn.hpp"
#include "../include/Rook.hpp"
#include "../include/Knight.hpp"
#include "../include/Bishop.hpp"
#include "../include/Queen.hpp"
#include "../include/King.hpp"
#include "../include/Game.hpp"
class Board
{
private:
    std::unique_ptr<Piece> Grid[8][8];

public:
    void Setup();
    Piece *GetPiece(int, int) const;
    bool IsEmpty(int, int) const;
    bool MovePiece(char, int, char, int);
};

#endif