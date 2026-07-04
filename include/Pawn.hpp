#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

class Pawn : public Piece
{
public:
    Pawn(Piece::Color);
    virtual bool IsValidMove(int, int, int, int) const override;
    virtual char GetSymbol() const override;
};

#endif