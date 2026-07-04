#include "../include/Dispaly.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

void Display::Draw(const Board &board)
{
    cout << left << setw(5) << "r\\c" << setw(5) << "a" << setw(5) << "b" << setw(5) << "c"
              << setw(5) << "d" << setw(5) << "e" << setw(5) << "f" << setw(5) << "g" << setw(5)
              << "h" << endl;
    cout << right << setw(44) << "_______________________________________\n";
    for (int row = 0; row < 8; row++)
    {
        cout << left << 8 - row << "  | ";
        for (int col = 0; col < 8; col++)
        {
            Piece *piece = board.GetPiece(row, col);
            if (piece != nullptr)
                cout << piece->GetSymbol() << setw(4) << static_cast<char>(piece->GetColor());
            else
                cout << setw(5) << ' ';
        }
        cout << endl;
    }
}