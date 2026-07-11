#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"

class King : public Piece
{
public:
    King(Color);
    virtual bool IsValidMove(const Move &) const override;
    virtual bool AttacksSquare(const Move &) const override;
    virtual std::string GetSymbol() const override;
    virtual Piece::Type GetType() const override;
};

#endif