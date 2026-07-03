#ifndef GAME_HPP
#define GAME_HPP

#include <string>
class Game
{
private:
    static int Turn;

public:
    std::string UserInput();
    bool ValidateMove();
    void GameState();

};

#endif