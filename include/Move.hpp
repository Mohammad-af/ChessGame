#ifndef MOVE_HPP
#define MOVE_HPP

#include <memory>
#include "Piece.hpp"

class Move
{
public:
    enum class Type
    {
        Normal,
        CastleKingSide,
        CastleQueenSide,
        Promotion,
        EnPassant
    };

private:
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
    Type moveType;
    Piece::Type promotionType;

public:
    Move(int, int, int, int);
    int GetFromRow() const;
    int GetFromCol() const;
    int GetToRow() const;
    int GetToCol() const;
    void SetMoveType(Type);
    Type GetMoveType() const;
    void SetPromotionType(Piece::Type);
    Piece::Type GetPromotionType() const;
};

#endif