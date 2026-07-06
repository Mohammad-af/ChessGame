#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Piece.hpp"

class Knight : public Piece
{
public:
    Knight(Color);
    virtual bool IsValidMove(const Move &) const override;
    virtual bool AttacksSquare(const Move &) const override;
    virtual std::string GetSymbol() const override;
    virtual Piece::PieceType GetType() const override;
};

#endif