#include "Board.hpp"
#include <iostream>

void Board::Setup()
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (row > 1 && row < 6)
                Grid[row][col] = nullptr;
            else if (row == 1)
                Grid[row][col] = std::make_unique<Pawn>(Piece::Color::Black);
            else if (row == 6)
                Grid[row][col] = std::make_unique<Pawn>(Piece::Color::White);
            else if (row == 0)
            {
                if (col == 0 || col == 7)
                    Grid[row][col] = std::make_unique<Rook>(Piece::Color::Black);
                else if (col == 1 || col == 6)
                    Grid[row][col] = std::make_unique<Knight>(Piece::Color::Black);
                else if (col == 2 || col == 5)
                    Grid[row][col] = std::make_unique<Bishop>(Piece::Color::Black);
                else if (col == 3)
                    Grid[row][col] = std::make_unique<Queen>(Piece::Color::Black);
                else
                {
                    Grid[row][col] = std::make_unique<King>(Piece::Color::Black);
                    BlackKingRow = row;
                    BlackKingCol = col;
                }
            }
            else
            {
                if (col == 0 || col == 7)
                    Grid[row][col] = std::make_unique<Rook>(Piece::Color::White);
                else if (col == 1 || col == 6)
                    Grid[row][col] = std::make_unique<Knight>(Piece::Color::White);
                else if (col == 2 || col == 5)
                    Grid[row][col] = std::make_unique<Bishop>(Piece::Color::White);
                else if (col == 3)
                    Grid[row][col] = std::make_unique<Queen>(Piece::Color::White);
                else
                {
                    Grid[row][col] = std::make_unique<King>(Piece::Color::White);
                    WhiteKingRow = row;
                    WhiteKingCol = col;
                }
            }
        }
    }
}

Piece *Board::GetPiece(int row, int col) const { return Grid[row][col].get(); }

bool Board::IsEmpty(int row, int col) const
{
    if (Grid[row][col] == nullptr)
        return true;
    return false;
}

bool Board::MovePiece(int row1, int row2, int col1, int col2)
{
    Grid[row2][col2] = move(Grid[row1][col1]);
    std::cout << "Successful move.\n";
    return true;
}

int Board::GetKingRow(Piece::Color color) const
{
    if (color == Piece::Color::White)
        return WhiteKingRow;
    else
        return BlackKingRow;
}

int Board::GetKingCol(Piece::Color color) const
{
    if (color == Piece::Color::White)
        return WhiteKingCol;
    else
        return BlackKingCol;
}

bool Board::IsPathClear(int row1, int row2, int col1, int col2, Piece *piece)
{
    switch (piece->GetType())
    {
    case Piece::PieceType::Rook:
    {
        int row_dir = (row2 > row1) ? 1 : ((row2 < row1) ? -1 : 0); // if(row2>row1)row_dir=1; else if(row2<row1)row_dir=-1; else row_dir=0;
        int col_dir = (col2 > col1) ? 1 : ((col2 < col1) ? -1 : 0);
        int current_row = row1 + row_dir;
        int current_col = col1 + col_dir;
        while (current_row != row2 || current_col != col2)
        {
            if (GetPiece(current_row, current_col) != nullptr)
                return false;
            current_row += row_dir;
            current_col += col_dir;
        }
        return true;
        break;
    }
    default:
        return true;
    }
}