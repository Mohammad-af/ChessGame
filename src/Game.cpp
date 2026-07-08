#include "Game.hpp"
#include <iostream>
#include <cctype>

int Game::turn = 1;

Move Game::UserInput() const
{
    std::string user_move;
    while (true)
    {
        if (GetTurnColor() == Piece::Color::White)
            std::cout << "White move: ";
        else
            std::cout << "Black move: ";
        std::cin >> user_move;
        if (user_move.length() != 4)
        {
            std::cout << "\nINVALID INPUT FORMAT! Use this format: a2a3\n\n";
            continue;
        }
        user_move[0] = std::tolower(user_move[0]);
        user_move[2] = std::tolower(user_move[2]);
        if (user_move[1] < '1' || user_move[1] > '8' || user_move[3] < '1' || user_move[3] > '8' || user_move[0] < 'a' || user_move[0] > 'h' || user_move[2] < 'a' || user_move[2] > 'h')
        {
            std::cout << "\nINVALID INPUT! Enter coloumn a-h and row 1-8.\n\n";
            continue;
        }
        break;
    }
    int row1, col1, row2, col2;
    col1 = user_move[0] - 'a'; // example: user_move[0] = 'b' = 98(ASCII); int col1 = 98 - 97 = 1; Grid[][col1] is the second column from left.
    col2 = user_move[2] - 'a';
    row1 = 7 - (user_move[1] - '1'); // example: user_move[1] = '2' = 50(ASCII); row1 = 7 - (50 - 49) = 6; Grid[row1][] is the second row from bottom.
    row2 = 7 - (user_move[3] - '1');
    return Move(row1, col1, row2, col2);
}

bool Game::ValidateMove(Move &move)
{
    if (board.IsEmpty(move.GetFromRow(), move.GetToCol()))
    {
        std::cout << "\nINVALID MOVE! The starting point has no pieces in it.\n\n";
        return false;
    }
    if (board.GetPiece(move.GetFromRow(), move.GetToCol())->GetColor() != GetTurnColor())
    {
        std::cout << "\nINVALID MOVE! You cannot move the opponent's piece.\n\n";
        return false;
    }
    if (move.GetFromRow() == move.GetToRow() && move.GetFromCol() == move.GetToCol())
    {
        std::cout << "\nINVALID MOVE! You cannot move to the same place.\n\n";
        return false;
    }
    Piece *piece = board.GetPiece(move.GetFromRow(), move.GetToCol());
    if (!(piece->IsValidMove(move)))
    {
        std::cout << "\nINVALID MOVE! This piece cannot move like this.\n\n";
        return false;
    }
    if (!(board.IsPathClear(move, piece)))
    {
        std::cout << "\nINVALID MOVE! The path is not clear or you cannot move diagonally with pawn here.\n\n";
        return false;
    }
    board.ApplyMove(move);
    Piece::Color opponent_color;
    if (GetTurnColor() == Piece::Color::White)
        opponent_color = Piece::Color::Black;
    if (GetTurnColor() == Piece::Color::Black)
        opponent_color = Piece::Color::White;
    if (board.IsSquareAttacked(board.GetKingRow(GetTurnColor()), board.GetKingCol(GetTurnColor()), opponent_color))
    {
        std::cout << "\nINVALID MOVE! You cannot put your King in danger.\n\n";
        board.UndoMove(move);
        return false;
    }
    if (piece->IsFirstMove())
        piece->MarkAsMoved();
    turn++;
    return true;
}

Game::GameStatus Game::GameState()
{
    Piece::Color opponent_color;
    if (GetTurnColor() == Piece::Color::White)
        opponent_color = Piece::Color::Black;
    if (GetTurnColor() == Piece::Color::Black)
        opponent_color = Piece::Color::White;
    if (board.IsSquareAttacked(board.GetKingRow(GetTurnColor()), board.GetKingCol(GetTurnColor()), opponent_color))
        return GameStatus::Check;
    return GameStatus::Play;
}

Piece::Color Game::GetTurnColor() const
{
    if (turn % 2 == 1)
        return Piece::Color::White;
    else
        return Piece::Color::Black;
}

std::string Game::GetTurnColorName() const
{
    if (GetTurnColor() == Piece::Color::White)
        return "White";
    return "Black";
}

void Game::Setup() { board.Setup(); }
void Game::Draw() const { Display::Draw(Game::board); }