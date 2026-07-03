#ifndef KING_HPP
#define KING_HPP

#include "../include/Piece.hpp"
class King : public Piece
{
public:
    King(Piece::Color);
    virtual bool IsValidMove(int, int, int, int) const override;
    virtual char GetSymbol() const override;
};

#endif