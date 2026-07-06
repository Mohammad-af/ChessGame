#include "Dispaly.hpp"
#include <iostream>

void Display::Draw(const Board &board)
{
    std::cout << "r\\c   " << "a    " << "b    " << "c    "
              << "d    " << "e    " << "f    " << "g    "
              << "h    " << std::endl;
    std::cout << "    _______________________________________\n";
    for (int row = 0; row < 8; row++)
    {
        std::cout << "   |    |    |    |    |    |    |    |    |" << std::endl
                  << 8 - row << "  | ";
        for (int col = 0; col < 8; col++)
        {
            Piece *piece = board.GetPiece(row, col);
            if (piece != nullptr)
                std::cout << piece->GetSymbol() << "  | ";
            else
                std::cout << "   | ";
        }
        std::cout << std::endl
                  << "   |____|____|____|____|____|____|____|____|" << std::endl;
    }
    std::cout << std::endl;
}