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
        Castling,
        EnPassant,
        Promotion
    };

private:
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
    Type moveType;

public:
    Move(int, int, int, int);
    int GetFromRow() const;
    int GetFromCol() const;
    int GetToRow() const;
    int GetToCol() const;
    void SetMoveType(Type);
    Type GetMoveType() const;
};

#endif