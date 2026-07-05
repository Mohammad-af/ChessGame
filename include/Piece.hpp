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
    enum class PieceType
    {
        Pawn,
        Knight,
        Bishop,
        Rook,
        Queen,
        King
    };

private:
    Color pieceColor; // White = 0, Black = 1
    bool firstMove = true;

public:
    Piece(Color);
    virtual ~Piece() = default;
    virtual bool IsValidMove(int, int, int, int, Color) const = 0;
    virtual std::string GetSymbol() const = 0;
    virtual PieceType GetType() const = 0;
    Color GetColor() const;
    bool IsFirstMove() const;
    void MarkAsMoved();
};

#endif