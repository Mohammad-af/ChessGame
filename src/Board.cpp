#include "Board.hpp"
#include <iostream>
#include <cmath>

void Board::Setup()
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (row > 1 && row < 6)
                grid[row][col] = nullptr;
            else if (row == 1)
                grid[row][col] = std::make_unique<Pawn>(Piece::Color::Black);
            else if (row == 6)
                grid[row][col] = std::make_unique<Pawn>(Piece::Color::White);
            else if (row == 0)
            {
                if (col == 0 || col == 7)
                    grid[row][col] = std::make_unique<Rook>(Piece::Color::Black);
                else if (col == 1 || col == 6)
                    grid[row][col] = std::make_unique<Knight>(Piece::Color::Black);
                else if (col == 2 || col == 5)
                    grid[row][col] = std::make_unique<Bishop>(Piece::Color::Black);
                else if (col == 3)
                    grid[row][col] = std::make_unique<Queen>(Piece::Color::Black);
                else
                {
                    grid[row][col] = std::make_unique<King>(Piece::Color::Black);
                    blackKingRow = row;
                    blackKingCol = col;
                }
            }
            else
            {
                if (col == 0 || col == 7)
                    grid[row][col] = std::make_unique<Rook>(Piece::Color::White);
                else if (col == 1 || col == 6)
                    grid[row][col] = std::make_unique<Knight>(Piece::Color::White);
                else if (col == 2 || col == 5)
                    grid[row][col] = std::make_unique<Bishop>(Piece::Color::White);
                else if (col == 3)
                    grid[row][col] = std::make_unique<Queen>(Piece::Color::White);
                else
                {
                    grid[row][col] = std::make_unique<King>(Piece::Color::White);
                    whiteKingRow = row;
                    whiteKingCol = col;
                }
            }
        }
    }
}

Piece *Board::GetPiece(int row, int col) const { return grid[row][col].get(); }

bool Board::IsEmpty(int row, int col) const
{
    if (grid[row][col] == nullptr)
        return true;
    return false;
}

void Board::ApplyMove(Move &move, const std::optional<Move> &last_move)
{
    Piece *piece = grid[move.GetFromRow()][move.GetFromCol()].get();
    if (piece->GetType() == Piece::Type::King)
    {
        if (piece->GetColor() == Piece::Color::White)
        {
            whiteKingRow = move.GetToRow();
            whiteKingCol = move.GetToCol();
        }
        else
        {
            blackKingRow = move.GetToRow();
            blackKingCol = move.GetToCol();
        }
    }
    if (move.GetMoveType() == Move::Type::EnPassant)
    {
        SetCapturedPiece(std::move(grid[last_move->GetToRow()][last_move->GetToCol()]));
        grid[move.GetToRow()][move.GetToCol()] = std::move(grid[move.GetFromRow()][move.GetFromCol()]);
    }
    else
    {
        SetCapturedPiece(std::move(grid[move.GetToRow()][move.GetToCol()]));
        grid[move.GetToRow()][move.GetToCol()] = std::move(grid[move.GetFromRow()][move.GetFromCol()]);
    }
}

void Board::UndoMove(Move &move, const std::optional<Move> &last_move)
{
    Piece *piece = grid[move.GetToRow()][move.GetToCol()].get();
    if (piece->GetType() == Piece::Type::King)
    {
        if (piece->GetColor() == Piece::Color::White)
        {
            whiteKingRow = move.GetFromRow();
            whiteKingCol = move.GetFromCol();
        }
        else
        {
            blackKingRow = move.GetFromRow();
            blackKingCol = move.GetFromCol();
        }
    }
    if (move.GetMoveType() == Move::Type::EnPassant)
    {
        grid[move.GetFromRow()][move.GetFromCol()] = std::move(grid[move.GetToRow()][move.GetToCol()]);
        grid[last_move->GetToRow()][last_move->GetToCol()] = ReleaseCapturedPiece();
    }
    else
    {
        grid[move.GetFromRow()][move.GetFromCol()] = std::move(grid[move.GetToRow()][move.GetToCol()]);
        grid[move.GetToRow()][move.GetToCol()] = ReleaseCapturedPiece();
    }
}

int Board::GetKingRow(Piece::Color color) const
{
    if (color == Piece::Color::White)
        return whiteKingRow;
    else
        return blackKingRow;
}

int Board::GetKingCol(Piece::Color color) const
{
    if (color == Piece::Color::White)
        return whiteKingCol;
    else
        return blackKingCol;
}

void Board::SetCapturedPiece(std::unique_ptr<Piece> &&piece) { capturedPiece = std::move(piece); }

std::unique_ptr<Piece> Board::ReleaseCapturedPiece() { return std::move(capturedPiece); }

bool Board::IsPathClear(Move &move, Piece *piece, const std::optional<Move> &last_move)
{
    Piece *end_move = GetPiece(move.GetToRow(), move.GetToCol());
    int row_dir = (move.GetToRow() > move.GetFromRow()) ? 1 : ((move.GetToRow() < move.GetFromRow()) ? -1 : 0); // if(move.GetToRow()>move.GetFromRow())row_dir=1; else if(move.GetToRow()<move.GetFromRow())row_dir=-1; else row_dir=0;
    int col_dir = (move.GetToCol() > move.GetFromCol()) ? 1 : ((move.GetToCol() < move.GetFromCol()) ? -1 : 0);
    int current_row = move.GetFromRow() + row_dir;
    int current_col = move.GetFromCol() + col_dir;
    if (end_move != nullptr && end_move->GetColor() == piece->GetColor())
        return false; // Friendly pieces cannot go on the same square.
    if (piece->GetType() != Piece::Type::Knight)
    {
        while ((current_row != move.GetToRow() || current_col != move.GetToCol()))
        {
            if (!IsEmpty(current_row, current_col))
                return false;
            current_row += row_dir;
            current_col += col_dir;
        }
    }
    if (piece->GetType() == Piece::Type::Pawn)
    {
        if (col_dir != 0)
        {
            if (end_move == nullptr)
            {
                if (!DetectEnPassant(move, last_move)) // If Pawn moves diagonally into an empty square it has to be EnPassant.
                    return false;
            }
        }
        else
        {
            if (end_move != nullptr)
                return false; // If Pawn moves vertically the square must be empty.
        }
    }
    return true;
}

bool Board::IsSquareAttacked(int square_row, int square_col, Piece::Color attacker_color, const std::optional<Move> &last_move)
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            Piece *piece = grid[row][col].get();
            if (piece != nullptr && piece->GetColor() == attacker_color)
            {
                Move move(row, col, square_row, square_col);
                if ((piece->GetType() == Piece::Type::Pawn && piece->AttacksSquare(move)) || (piece->GetType() != Piece::Type::Pawn && piece->AttacksSquare(move) && IsPathClear(move, piece, last_move)))
                    return true;
            }
        }
    }
    return false;
}

bool Board::DetectEnPassant(Move &move, const std::optional<Move> &last_move)
{
    if (!last_move.has_value())
        return false;
    if (std::abs(last_move->GetFromRow() - last_move->GetToRow()) != 2)
        return false;
    if (last_move->GetToRow() == move.GetFromRow() && std::abs(last_move->GetToCol() - move.GetFromCol()) != 1)
        return false;
    int col_dir = (move.GetToCol() > move.GetFromCol()) ? 1 : ((move.GetToCol() < move.GetFromCol()) ? -1 : 0);
    if (col_dir == 0)
        return false;
    Piece *end_move = GetPiece(move.GetToRow(), move.GetToCol());
    if (end_move != nullptr)
        return false;
    move.SetMoveType(Move::Type::EnPassant);
    return true;
}

bool Board::IsMoveLegal(Move &move, Piece::Color turn_color, const std::optional<Move> &last_move)
{ // HasLegalMove calls this function and some of this conditions are checked in that function but for safety and also making this function not fully reliable on function HasLegalMove, we will still check those conditions in this function.
    move.SetMoveType(Move::Type::Normal);
    if (IsEmpty(move.GetFromRow(), move.GetFromCol()))
        return false;
    if (GetPiece(move.GetFromRow(), move.GetFromCol())->GetColor() != turn_color)
        return false;
    if (move.GetFromRow() == move.GetToRow() && move.GetFromCol() == move.GetToCol())
        return false;
    Piece *piece = GetPiece(move.GetFromRow(), move.GetFromCol());
    if (!(piece->IsValidMove(move)))
        return false;
    if (!(IsPathClear(move, piece, last_move)))
        return false;
    ApplyMove(move, last_move);
    Piece::Color opponent_color = (turn_color == Piece::Color::White) ? Piece::Color::Black : Piece::Color::White;
    if (IsSquareAttacked(GetKingRow(turn_color), GetKingCol(turn_color), opponent_color, last_move))
    {
        UndoMove(move, last_move);
        return false;
    }
    UndoMove(move, last_move);
    return true;
}

bool Board::HasLegalMove(Piece::Color turnColor, const std::optional<Move> &last_move)
{
    for (int from_row = 0; from_row < 8; from_row++)
    {
        for (int from_col = 0; from_col < 8; from_col++)
        {
            if (IsEmpty(from_row, from_col))
                continue;
            Piece *piece = GetPiece(from_row, from_col);
            if (piece->GetColor() != turnColor)
                continue;
            for (int to_row = 0; to_row < 8; to_row++)
            {
                for (int to_col = 0; to_col < 8; to_col++)
                {
                    if (from_row == to_row && from_col == to_col)
                        continue;
                    Move move(from_row, from_col, to_row, to_col);
                    if (IsMoveLegal(move, turnColor, last_move))
                        return true;
                }
            }
        }
    }
    return false;
}