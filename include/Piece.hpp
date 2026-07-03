#ifndef PIECE_HPP
#define PIECE_HPP

class Piece
{
public:
    enum class Color : char
    {
        WHITE = 'w',
        BLACK = 'b'
    };

private:
    Color PieceColor; // White = 0, Black = 1

public:
    Piece(Color);
    virtual bool IsValidMove(int, int, int, int) const = 0;
    virtual char GetSymbol() const = 0;
    virtual ~Piece() = default;
    Color GetColor() const;
};

#endif