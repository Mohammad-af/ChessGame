#ifndef ROOK_HPP
#define ROOK_HPP

#include "Piece.hpp"

class Rook : public Piece
{
public:
    Rook(Piece::Color);
    virtual bool IsValidMove(int, int, int, int) const override;
    virtual bool AttacksSquare(int, int, int, int) const override;
    virtual std::string GetSymbol() const override;
    virtual Piece::PieceType GetType() const override;
};

#endif