#include "Board.hpp"
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

bool Board::IsEmpty(int row, int col) const { return grid[row][col] == nullptr; }

void Board::ApplyMove(Move &move, const std::optional<Move> &last_move)
{
    Piece *piece = GetPiece(move.GetFromRow(), move.GetFromCol());
    SetCapturedPiece(nullptr);
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
    if (move.GetMoveType() == Move::Type::CastleKingSide)
    {
        grid[move.GetToRow()][move.GetToCol()] = std::move(grid[move.GetFromRow()][move.GetFromCol()]);
        grid[move.GetToRow()][5] = std::move(grid[move.GetFromRow()][7]);
    }
    else if (move.GetMoveType() == Move::Type::CastleQueenSide)
    {
        grid[move.GetToRow()][move.GetToCol()] = std::move(grid[move.GetFromRow()][move.GetFromCol()]);
        grid[move.GetToRow()][3] = std::move(grid[move.GetFromRow()][0]);
    }
    else if (move.GetMoveType() == Move::Type::Promotion)
    {
        if (move.GetFromCol() != move.GetToCol())
            SetCapturedPiece(std::move(grid[move.GetToRow()][move.GetToCol()]));
        grid[move.GetToRow()][move.GetToCol()] = std::move(grid[move.GetFromRow()][move.GetFromCol()]);
        promotedPawn = std::move(grid[move.GetToRow()][move.GetToCol()]);
        if (move.GetPromotionType() == Piece::Type::Queen)
            grid[move.GetToRow()][move.GetToCol()] = std::make_unique<Queen>(piece->GetColor());
        else if (move.GetPromotionType() == Piece::Type::Rook)
            grid[move.GetToRow()][move.GetToCol()] = std::make_unique<Rook>(piece->GetColor());
        else if (move.GetPromotionType() == Piece::Type::Knight)
            grid[move.GetToRow()][move.GetToCol()] = std::make_unique<Knight>(piece->GetColor());
        else
            grid[move.GetToRow()][move.GetToCol()] = std::make_unique<Bishop>(piece->GetColor());
    }
    else if (move.GetMoveType() == Move::Type::EnPassant)
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
    Piece *piece = GetPiece(move.GetToRow(), move.GetToCol());
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
    if (move.GetMoveType() == Move::Type::CastleKingSide)
    {
        grid[move.GetFromRow()][move.GetFromCol()] = std::move(grid[move.GetToRow()][move.GetToCol()]);
        grid[move.GetFromRow()][7] = std::move(grid[move.GetToRow()][5]);
    }
    else if (move.GetMoveType() == Move::Type::CastleQueenSide)
    {
        grid[move.GetFromRow()][move.GetFromCol()] = std::move(grid[move.GetToRow()][move.GetToCol()]);
        grid[move.GetFromRow()][0] = std::move(grid[move.GetToRow()][3]);
    }
    else if (move.GetMoveType() == Move::Type::Promotion)
    {
        grid[move.GetToRow()][move.GetToCol()] = ReleasePromotedPawn();
        grid[move.GetFromRow()][move.GetFromCol()] = std::move(grid[move.GetToRow()][move.GetToCol()]);
        promotedPawn = nullptr;
        if (move.GetFromCol() != move.GetToCol())
            grid[move.GetToRow()][move.GetToCol()] = ReleaseCapturedPiece();
    }
    else if (move.GetMoveType() == Move::Type::EnPassant)
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

bool Board::HasCapturedPiece() const { return capturedPiece != nullptr; }

void Board::SetPromotedPawn(std::unique_ptr<Piece> &&pawn) { promotedPawn = std::move(pawn); }

std::unique_ptr<Piece> Board::ReleasePromotedPawn() { return std::move(promotedPawn); }

std::string Board::GetPositionString(Piece::Color turn_color, const std::optional<Move> &last_move) const
{
    std::string position;
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            Piece *piece = grid[row][col].get();
            if (grid[row][col] == nullptr)
                position += "_";
            else if (piece->GetType() == Piece::Type::Pawn)
                position += (piece->GetColor() == Piece::Color::White) ? 'P' : 'p';
            else if (piece->GetType() == Piece::Type::Rook)
                position += (piece->GetColor() == Piece::Color::White) ? 'R' : 'r';
            else if (piece->GetType() == Piece::Type::Knight)
                position += (piece->GetColor() == Piece::Color::White) ? 'N' : 'n';
            else if (piece->GetType() == Piece::Type::Bishop)
                position += (piece->GetColor() == Piece::Color::White) ? 'B' : 'b';
            else if (piece->GetType() == Piece::Type::Queen)
                position += (piece->GetColor() == Piece::Color::White) ? 'Q' : 'q';
            else
                position += (piece->GetColor() == Piece::Color::White) ? 'K' : 'k';
        }
    }
    position += (turn_color == Piece::Color::White) ? "|w|" : "|b|";
    AddCastlingRights(position, Piece::Color::White);
    AddCastlingRights(position, Piece::Color::Black);
    position += '|';
    if (last_move.has_value())
    {
        Piece *pawn = GetPiece(last_move->GetToRow(), last_move->GetToCol());
        if (pawn->GetType() == Piece::Type::Pawn && std::abs(last_move->GetFromRow() - last_move->GetToRow()) == 2)
        {
            char row = '1' + (7 - (last_move->GetFromRow() + last_move->GetToRow()) / 2);
            char col = (last_move->GetFromCol()) + 'a';
            position += col;
            position += row;
        }
    }
    return position;
}

void Board::AddCastlingRights(std::string &position, Piece::Color color) const
{
    const int white_side_rook_row = 7, black_side_rook_row = 0, queen_side_rook_col = 0, king_side_rook_col = 7;
    Piece *king = (color == Piece::Color::White) ? GetPiece(whiteKingRow, whiteKingCol) : GetPiece(blackKingRow, blackKingCol);
    if (king->IsFirstMove())
    {
        Piece *king_side_rook = (color == Piece::Color::White) ? GetPiece(white_side_rook_row, king_side_rook_col) : GetPiece(black_side_rook_row, king_side_rook_col);
        Piece *queen_side_rook = (color == Piece::Color::White) ? GetPiece(white_side_rook_row, queen_side_rook_col) : GetPiece(black_side_rook_row, queen_side_rook_col);
        if (king_side_rook != nullptr && king_side_rook->GetType() == Piece::Type::Rook && king_side_rook->IsFirstMove())
            position += (color == Piece::Color::White) ? 'K' : 'k';
        if (queen_side_rook != nullptr && queen_side_rook->GetType() == Piece::Type::Rook && queen_side_rook->IsFirstMove())
            position += (color == Piece::Color::White) ? 'Q' : 'q';
    }
}
bool Board::IsPathClear(const Move &move, Piece *piece, const std::optional<Move> &last_move) const
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
    if (piece->GetType() == Piece::Type::Pawn && col_dir == 0 && end_move != nullptr)
        return false; // If Pawn moves vertically the square must be empty.
    return true;
}

bool Board::IsSquareAttacked(int square_row, int square_col, Piece::Color attacker_color, const std::optional<Move> &last_move) const
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            Piece *piece = GetPiece(row, col);
            if (piece != nullptr && piece->GetColor() == attacker_color)
            {
                Move move(row, col, square_row, square_col);
                if (piece->AttacksSquare(move) && IsPathClear(move, piece, last_move))
                    return true;
            }
        }
    }
    return false;
}

bool Board::DetectCastling(Move &move, const std::optional<Move> &last_move)
{
    Piece *piece = GetPiece(move.GetFromRow(), move.GetFromCol());
    if (!piece->IsFirstMove())
        return false;
    int rook_row = (piece->GetColor() == Piece::Color::White) ? 7 : 0;
    int rook_col = (move.GetToCol() == 6) ? 7 : 0;
    Piece *rook = GetPiece(rook_row, rook_col);
    if (rook == nullptr || rook->GetType() != Piece::Type::Rook)
        return false;
    Piece::Color opponent_color = (piece->GetColor() == Piece::Color::White) ? Piece::Color::Black : Piece::Color::White;
    const int queen_side_rook_path_col = 1;
    if (move.GetToCol() == 6)
    {
        if (rook->IsFirstMove() && !IsSquareAttacked(move.GetFromRow(), move.GetFromCol(), opponent_color, last_move) && !IsSquareAttacked(move.GetFromRow(), 5, opponent_color, last_move) && !IsSquareAttacked(move.GetFromRow(), 6, opponent_color, last_move))
        {
            move.SetMoveType(Move::Type::CastleKingSide);
            return true;
        }
    }
    else
    {
        if (rook->IsFirstMove() && IsEmpty(rook_row, queen_side_rook_path_col) && !IsSquareAttacked(move.GetFromRow(), move.GetFromCol(), opponent_color, last_move) && !IsSquareAttacked(move.GetFromRow(), 3, opponent_color, last_move) && !IsSquareAttacked(move.GetFromRow(), 2, opponent_color, last_move))
        {
            move.SetMoveType(Move::Type::CastleQueenSide);
            return true;
        }
    }
    return false;
}

bool Board::DetectPromotion(Move &move)
{
    if (move.GetToRow() != 0 && move.GetToRow() != 7)
        return false;
    move.SetMoveType(Move::Type::Promotion);
    return true;
}

bool Board::DetectEnPassant(Move &move, const std::optional<Move> &last_move)
{
    if (!last_move.has_value())
        return false;
    if (std::abs(last_move->GetFromRow() - last_move->GetToRow()) != 2)
        return false;
    if (last_move->GetToRow() != move.GetFromRow() || std::abs(last_move->GetToCol() - move.GetFromCol()) != 1)
        return false;
    int col_dir = (move.GetToCol() > move.GetFromCol()) ? 1 : -1;
    Piece *end_move = GetPiece(move.GetToRow(), move.GetToCol());
    if (end_move != nullptr)
        return false;
    move.SetMoveType(Move::Type::EnPassant);
    return true;
}

bool Board::InsufficientMaterial() const
{
    int white_bishop_num = 0;
    int black_bishop_num = 0;
    int white_knight_num = 0;
    int black_knight_num = 0;
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (GetPiece(row, col) == nullptr)
                continue;
            Piece *piece = GetPiece(row, col);
            if (piece->GetType() == Piece::Type::Queen || piece->GetType() == Piece::Type::Rook || piece->GetType() == Piece::Type::Pawn)
                return false;
            if (piece->GetType() == Piece::Type::Bishop)
            {
                if (piece->GetColor() == Piece::Color::White)
                    white_bishop_num++;
                else
                    black_bishop_num++;
            }
            if (piece->GetType() == Piece::Type::Knight)
            {
                if (piece->GetColor() == Piece::Color::White)
                    white_knight_num++;
                else
                    black_knight_num++;
            }
        }
    }
    if (white_bishop_num >= 2 || white_knight_num >= 2 || black_bishop_num >= 2 || black_knight_num >= 2)
        return false;
    if ((white_bishop_num == 1 && white_knight_num == 1) || (black_bishop_num == 1 && black_knight_num == 1))
        return false;
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
    if (piece->GetType() == Piece::Type::Pawn)
    {
        if (DetectPromotion(move))
            move.SetPromotionType(Piece::Type::Queen);
        else if (move.GetFromCol() != move.GetToCol() && IsEmpty(move.GetToRow(), move.GetToCol()) && !DetectEnPassant(move, last_move))
            return false;
    }
    if (piece->GetType() == Piece::Type::King && std::abs(move.GetFromCol() - move.GetToCol()) == 2)
    {
        if (!DetectCastling(move, last_move))
            return false;
    }
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