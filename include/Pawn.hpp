#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

class Pawn : public Piece
{
public:
    Pawn(Color);
    virtual bool IsValidMove(const Move &) const override;
    virtual bool AttacksSquare(const Move &) const override;
    virtual std::string GetSymbol() const override;
    virtual Piece::Type GetType() const override;
};

#endif