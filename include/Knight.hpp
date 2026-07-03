#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "../include/Piece.hpp"
class Knight : public Piece
{
public:
    Knight(Piece::Color);
    virtual bool IsValidMove(int, int, int, int) const override;
    virtual char GetSymbol() const override;
};

#endif