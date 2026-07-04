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
    std::string UserInput() const;
    bool ValidateMove(const std::string &);
    void GameState();
    bool IsCheck() const;
    void Setup();
    void Draw() const;
};

#endif