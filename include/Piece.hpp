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

protected:
    bool FirstMove = true;

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
    virtual bool IsValidMove(int, int, int, int, Color) const = 0;
    virtual std::string GetSymbol() const = 0;
    Color GetColor() const;
    virtual PieceType GetType() const = 0;
    bool IsFirstMove() const;
    void MadeFisrtMove();
};

#endif