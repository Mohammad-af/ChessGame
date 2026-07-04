#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include "Board.hpp"
#include "Dispaly.hpp"

class Game
{
private:
    Board board;
    static int Turn;

public:
    enum class GameStatus
    {
        Play,
        Check,
        Checkmate,
        Stalemate
    };
    std::string UserInput() const;
    bool ValidateMove(const std::string &);
    void GameState();
    bool IsSquareAttacked(int, int, Piece::Color) const;
    Piece::Color TurnColor() const;
    void Setup();
    void Draw() const;
};

#endif