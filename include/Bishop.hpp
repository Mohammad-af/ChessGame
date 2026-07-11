#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "Piece.hpp"

class Bishop : public Piece
{
public:
    Bishop(Color);
    virtual bool IsValidMove(const Move &) const override;
    virtual bool AttacksSquare(const Move &) const override;
    virtual std::string GetSymbol() const override;
    virtual Piece::Type GetType() const override;
};

#endif