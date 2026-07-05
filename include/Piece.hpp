#ifndef PIECE_HPP
#define PIECE_HPP

#include <string>

class Piece
{
public:
    enum class Color : char
    {
        White = 'w',
        Black = 'b'
    };

private:
    Color PieceColor; // White = 0, Black = 1

public:
    enum class PieceType
    {
        Pawn,
        Knight,
        Bishop,
        Rook,
        Queen,
        King
    };
    Piece(Color);
    virtual ~Piece() = default;
    virtual bool IsValidMove(int, int, int, int) const = 0;
    virtual std::string GetSymbol() const = 0;
    Color GetColor() const;
    virtual PieceType GetType() const = 0;
};

#endif