#include "Game.hpp"
#include <iostream>
#include <cctype> // For character functions like std::tolower(int).
#include <cmath>

int Game::turn = 1;

Move Game::UserInput() const
{
    std::string user_move;
    while (true)
    {
        std::cout << GetColorName(GetTurnColor()) << " move: ";
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
    int from_row, from_col, to_row, to_col;
    from_col = user_move[0] - 'a'; // example: user_move[0] = 'b' = 98(ASCII); int col1 = 98 - 97 = 1; Grid[][col1] is the second column from left.
    to_col = user_move[2] - 'a';
    from_row = 7 - (user_move[1] - '1'); // example: user_move[1] = '2' = 50(ASCII); row1 = 7 - (50 - 49) = 6; Grid[row1][] is the second row from bottom.
    to_row = 7 - (user_move[3] - '1');
    return Move(from_row, from_col, to_row, to_col);
}

bool Game::ValidateMove(Move &move)
{
    move.SetMoveType(Move::Type::Normal);
    if (board.IsEmpty(move.GetFromRow(), move.GetFromCol()))
    {
        std::cout << "\nINVALID MOVE! The starting point has no pieces in it.\n\n";
        return false;
    }
    if (board.GetPiece(move.GetFromRow(), move.GetFromCol())->GetColor() != GetTurnColor())
    {
        std::cout << "\nINVALID MOVE! You cannot move the opponent's piece.\n\n";
        return false;
    }
    if (move.GetFromRow() == move.GetToRow() && move.GetFromCol() == move.GetToCol())
    {
        std::cout << "\nINVALID MOVE! You cannot move to the same place.\n\n";
        return false;
    }
    Piece *piece = board.GetPiece(move.GetFromRow(), move.GetFromCol());
    if (!(piece->IsValidMove(move)))
    {
        std::cout << "\nINVALID MOVE! This piece cannot move like this.\n\n";
        return false;
    }
    if (!(board.IsPathClear(move, piece, lastMove)))
    {
        std::cout << "\nINVALID MOVE! The path is not clear.\n\n";
        return false;
    }
    if (piece->GetType() == Piece::Type::Pawn)
    {
        if (board.DetectPromotion(move))
        {
            char piece_type;
            while (true)
            {
                std::cout << "Promote to (Q/R/N/B): ";
                std::cin >> piece_type;
                piece_type = std::toupper(piece_type);
                if (piece_type == 'Q' || piece_type == 'R' || piece_type == 'N' || piece_type == 'B')
                    break;
                std::cout << "INVALID INPUT! Enter Q, R, N or B.\n";
            }
            switch (piece_type)
            {
            case 'Q':
                move.SetPromotionType(Piece::Type::Queen);
                break;
            case 'R':
                move.SetPromotionType(Piece::Type::Rook);
                break;
            case 'N':
                move.SetPromotionType(Piece::Type::Knight);
                break;
            case 'B':
                move.SetPromotionType(Piece::Type::Bishop);
                break;
            }
        }
        else if (move.GetFromCol() != move.GetToCol() && board.IsEmpty(move.GetToRow(), move.GetToCol()) && !board.DetectEnPassant(move, lastMove))
        {
            std::cout << "\nINVALID MOVE! You cannot move diagonally to an empty space with the Pawn unless it's En Passant and the conditions are met.\n\n";
            return false;
        }
    }
    else if (piece->GetType() == Piece::Type::King && std::abs(move.GetFromCol() - move.GetToCol()) == 2)
    {
        if (!board.DetectCastling(move, lastMove))
        {
            std::cout << "\nINVALID MOVE! You cannot move 2 squares with the King unless it's Castling and the conditions are met.\n\n";
            return false;
        }
    }
    board.ApplyMove(move, lastMove);
    Piece::Color opponent_color = GetOpponentColor();
    if (board.IsSquareAttacked(board.GetKingRow(GetTurnColor()), board.GetKingCol(GetTurnColor()), opponent_color, lastMove))
    {
        std::cout << "\nINVALID MOVE! You cannot put your King in danger.\n\n";
        board.UndoMove(move, lastMove);
        return false;
    }
    if (piece->IsFirstMove())
        piece->MarkAsMoved();
    lastMove = move;
    if (board.HasCapturedPiece() || piece->GetType() == Piece::Type::Pawn)
        halfMoveCounter = 0;
    else
        halfMoveCounter++;
    turn++;
    return true;
}

Game::Status Game::GameState()
{
    if (board.InsufficientMaterial())
        return Status::InsufficientMaterial;
    if (halfMoveCounter >= 100)
        return Status::FiftyMoveRule;
    Piece::Color opponent_color = GetOpponentColor();
    if (board.IsSquareAttacked(board.GetKingRow(GetTurnColor()), board.GetKingCol(GetTurnColor()), opponent_color, lastMove))
    {
        if (!board.HasLegalMove(GetTurnColor(), lastMove))
            return Status::Checkmate;
        else
            return Status::Check;
    }
    else
    {
        if (!board.HasLegalMove(GetTurnColor(), lastMove))
            return Status::Stalemate;
        else
            return Status::Play;
    }
}

Piece::Color Game::GetTurnColor() const
{
    if (turn % 2 == 1)
        return Piece::Color::White;
    else
        return Piece::Color::Black;
}

Piece::Color Game::GetOpponentColor() const
{
    if (turn % 2 == 1)
        return Piece::Color::Black;
    else
        return Piece::Color::White;
}

std::string Game::GetColorName(Piece::Color color) const
{
    if (color == Piece::Color::White)
        return "White";
    return "Black";
}

void Game::Setup() { board.Setup(); }
void Game::Draw() const { Display::Draw(Game::board); }