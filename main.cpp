#include <iostream>
#include <string>
#include "include/Dispaly.hpp"
#include "include/Game.hpp"
using namespace std;
int main()
{
    bool run_game = true;
    int turn = 1;
    string user_move;
    Board board;
    Game game;
    board.Setup();
    while (run_game)
    {
        system("cls");
        Display::Draw(board);
        user_move = game.UserInput();
        if(board.MovePiece(user_move[0],user_move[1],user_move[2],user_move[3]))
            game.GameState();
        system("pause");
    }
    return 0;
}