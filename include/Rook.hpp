#ifndef ROOK_HPP
#define ROOK_HPP

#include "../include/Piece.hpp"
class Rook : public Piece
{
public:
    Rook(Piece::Color);
    virtual bool IsValidMove(int, int, int, int) const override;
    virtual char GetSymbol() const override;
};

#endif