#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <optional>      // For std::optional<Move> data type. It's added because you need to pass valuses for the Move constructor and in main.cpp we create Game data type without arguments.
#include <unordered_map> // For std::unordered_map<std::string, int> data type. It's like a organized vector.
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
        Stalemate,
        ThreefoldRepetition,
        InsufficientMaterial,
        FiftyMoveRule
    };

private:
    Board board;
    static int turn;
    std::optional<Move> lastMove = std::nullopt;
    int halfMoveCounter;                                  // This is for fifty rule move.
    std::unordered_map<std::string, int> positionHistory; // Key: std::string  Value: int

public:
    Game();
    bool UserInput(Move &);
    bool ValidateMove(Move &);
    Status GameState();
    Piece::Color GetTurnColor() const;
    Piece::Color GetOpponentColor() const;
    std::string GetColorName(Piece::Color) const;
    void SaveGame(const std::string &) const;
    void LoadGame(const std::string &);
    void Draw() const;
};

#endif