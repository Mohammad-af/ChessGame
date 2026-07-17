#ifndef BOARD_HPP
#define BOARD_HPP

#include <memory> // For data type std::unique_ptr<Piece>.
#include <string>
#include <optional>
#include "Piece.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"
#include "Move.hpp"

class Board
{
private:
    std::unique_ptr<Piece> grid[8][8];
    int whiteKingRow;
    int whiteKingCol;
    int blackKingRow;
    int blackKingCol;
    std::unique_ptr<Piece> capturedPiece = nullptr;
    std::unique_ptr<Piece> promotedPawn = nullptr;

public:
    void Setup();
    Piece *GetPiece(int, int) const;
    bool IsEmpty(int, int) const;
    void ApplyMove(Move &, const std::optional<Move> &);
    void UndoMove(Move &, const std::optional<Move> &);
    int GetKingRow(Piece::Color) const;
    int GetKingCol(Piece::Color) const;
    void SetCapturedPiece(std::unique_ptr<Piece> &&);
    std::unique_ptr<Piece> ReleaseCapturedPiece();
    bool HasCapturedPiece() const;
    void SetPromotedPawn(std::unique_ptr<Piece> &&);
    std::unique_ptr<Piece> ReleasePromotedPawn();
    bool IsPathClear(const Move &, Piece *, const std::optional<Move> &) const;
    bool IsSquareAttacked(int, int, Piece::Color, const std::optional<Move> &) const;
    bool DetectCastling(Move &, const std::optional<Move> &);
    bool DetectEnPassant(Move &, const std::optional<Move> &);
    bool DetectPromotion(Move &move);
    bool InsufficientMaterial() const;
    bool IsMoveLegal(Move &, Piece::Color, const std::optional<Move> &);
    bool HasLegalMove(Piece::Color, const std::optional<Move> &);
};

#endif