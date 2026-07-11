#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "Piece.hpp"

class Queen : public Piece
{
public:
    Queen(Color);
    virtual bool IsValidMove(const Move &) const override;
    virtual bool AttacksSquare(const Move &) const override;
    virtual std::string GetSymbol() const override;
    virtual Piece::Type GetType() const override;
};

#endif