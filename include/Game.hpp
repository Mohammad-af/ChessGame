#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <optional> // For std::optional<Move> data type. It's added because you need to pass valuses for the Move constructor and in main.cpp we create Game data type without arguments.
#include "Board.hpp"
#include "Dispaly.hpp"
#include "Move.hpp"

class Game
{
public:
    enum class Status
    {
        Play,
        Check,
        Checkmate,
        Stalemate
    };

private:
    Board board;
    static int turn;
    std::optional<Move> lastMove = std::nullopt;

public:
    Move UserInput() const;
    bool ValidateMove(Move &);
    Status GameState();
    Piece::Color GetTurnColor() const;
    Piece::Color GetOpponentColor() const;
    std::string GetColorName(Piece::Color) const;
    void Setup();
    void Draw() const;
};

#endif