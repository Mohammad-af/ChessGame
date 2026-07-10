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

void Board::ApplyMove(Move &move)
{
    Piece *piece = grid[move.GetFromRow()][move.GetFromCol()].get();
    if (piece->GetType() == Piece::PieceType::King)
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
    move.SetCapturedPiece(std::move(grid[move.GetToRow()][move.GetToCol()]));
    grid[move.GetToRow()][move.GetToCol()] = std::move(grid[move.GetFromRow()][move.GetFromCol()]);
}

void Board::UndoMove(Move &move)
{
    Piece *piece = grid[move.GetToRow()][move.GetToCol()].get();
    if (piece->GetType() == Piece::PieceType::King)
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
    grid[move.GetFromRow()][move.GetFromCol()] = std::move(grid[move.GetToRow()][move.GetToCol()]);
    grid[move.GetToRow()][move.GetToCol()] = move.ReleaseCapturedPiece();
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

bool Board::IsPathClear(const Move &move, Piece *piece)
{
    Piece *end_move = GetPiece(move.GetToRow(), move.GetToCol());
    int row_dir = (move.GetToRow() > move.GetFromRow()) ? 1 : ((move.GetToRow() < move.GetFromRow()) ? -1 : 0); // if(move.GetToRow()>move.GetFromRow())row_dir=1; else if(move.GetToRow()<move.GetFromRow())row_dir=-1; else row_dir=0;
    int col_dir = (move.GetToCol() > move.GetFromCol()) ? 1 : ((move.GetToCol() < move.GetFromCol()) ? -1 : 0);
    int current_row = move.GetFromRow() + row_dir;
    int current_col = move.GetFromCol() + col_dir;
    if (end_move != nullptr && end_move->GetColor() == piece->GetColor())
        return false; // Friendly pieces cannot go on the same square.
    if (piece->GetType() != Piece::PieceType::Knight)
    {
        while ((current_row != move.GetToRow() || current_col != move.GetToCol()))
        {
            if (!IsEmpty(current_row, current_col))
                return false;
            current_row += row_dir;
            current_col += col_dir;
        }
    }
    if (piece->GetType() == Piece::PieceType::Pawn)
    {
        if (col_dir != 0)
        {
            if (end_move == nullptr)
                return false; // If Pawn moves diagonally it has to take an opponent's piece.
        }
        else
        {
            if (end_move != nullptr)
                return false; // If Pawn moves vertically the square must be empty.
        }
    }
    return true;
}

bool Board::IsSquareAttacked(int square_row, int square_col, Piece::Color attacker_color)
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            Piece *piece = grid[row][col].get();
            if (piece != nullptr && piece->GetColor() == attacker_color)
            {
                Move move(row, col, square_row, square_col);
                if ((piece->GetType() == Piece::PieceType::Pawn && piece->AttacksSquare(move)) || (piece->GetType() != Piece::PieceType::Pawn && piece->AttacksSquare(move) && IsPathClear(move, piece)))
                    return true;
            }
        }
    }
    return false;
}

bool Board::IsMoveLegal(Move &move, Piece::Color turn_color)
{   // HasLegalMove calls this function and some of this conditions are checked in that function but for safety and also making this function not fully reliable on function HasLegalMove, we will still check those conditions in this function.
    if (IsEmpty(move.GetFromRow(), move.GetFromCol()))
        return false;
    if (GetPiece(move.GetFromRow(), move.GetFromCol())->GetColor() != turn_color)
        return false;
    if (move.GetFromRow() == move.GetToRow() && move.GetFromCol() == move.GetToCol())
        return false;
    Piece *piece = GetPiece(move.GetFromRow(), move.GetFromCol());
    if (!(piece->IsValidMove(move)))
        return false;
    if (!(IsPathClear(move, piece)))
        return false;
    ApplyMove(move);
    Piece::Color opponent_color = (turn_color == Piece::Color::White) ? Piece::Color::Black : Piece::Color::White;
    if (IsSquareAttacked(GetKingRow(turn_color), GetKingCol(turn_color), opponent_color))
    {
        UndoMove(move);
        return false;
    }
    UndoMove(move);
    return true;
}

bool Board::HasLegalMove(Piece::Color turnColor)
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
                    if (IsMoveLegal(move, turnColor))
                        return true;
                }
            }
        }
    }
    return false;
}