#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Piece.hpp"

class Knight : public Piece
{
public:
    Knight(Color);
    virtual bool IsValidMove(int, int, int, int) const override;
    virtual bool AttacksSquare(int, int, int, int) const override;
    virtual std::string GetSymbol() const override;
    virtual Piece::PieceType GetType() const override;
};

#endif