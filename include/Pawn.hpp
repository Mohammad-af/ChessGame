#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

class Pawn : public Piece
{
public:
    Pawn(Color);
    virtual bool IsValidMove(int, int, int, int) const override;
    virtual bool AttacksSquare(int, int, int, int) const override;
    virtual std::string GetSymbol() const override;
    virtual Piece::PieceType GetType() const override;
};

#endif