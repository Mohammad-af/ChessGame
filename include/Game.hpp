#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include "Board.hpp"
#include "Dispaly.hpp"

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
    std::string UserInput() const;
    bool ValidateMove(const std::string &);
    GameStatus GameState();
    Piece::Color GetTurnColor() const;
    std::string GetColorTurnName() const;
    void Setup();
    void Draw() const;
};

#endif