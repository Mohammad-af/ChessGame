#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"

class King : public Piece
{
public:
    King(Color);
    virtual bool IsValidMove(int, int, int, int) const override;
    virtual bool AttacksSquare(int, int, int, int) const override;
    virtual std::string GetSymbol() const override;
    virtual Piece::PieceType GetType() const override;
};

#endif