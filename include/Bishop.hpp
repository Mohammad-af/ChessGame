#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "../include/Piece.hpp"
class Bishop : public Piece
{
public:
    Bishop(Piece::Color);
    virtual bool IsValidMove(int, int, int, int) const override;
    virtual char GetSymbol() const override;
};

#endif