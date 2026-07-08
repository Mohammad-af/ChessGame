#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include "Board.hpp"
#include "Dispaly.hpp"
#include "Move.hpp"

class Game
{
public:
    enum class GameStatus
    {
        Play,
        Check,
        Checkmate,
        Stalemate
    };

private:
    Board board;
    static int turn;

public:
    Move UserInput() const;
    bool ValidateMove(Move &);
    GameStatus GameState();
    Piece::Color GetTurnColor() const;
    std::string GetTurnColorName() const;
    void Setup();
    void Draw() const;
};

#endif