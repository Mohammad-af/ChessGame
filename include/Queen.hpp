#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "Piece.hpp"

class Queen : public Piece
{
public:
    Queen(Piece::Color);
    virtual bool IsValidMove(int, int, int, int) const override;
    virtual char GetSymbol() const override;
};

#endif