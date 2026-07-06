#include "Console.hpp"
#include <iostream>
#include <limits>
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#endif

void SetupConsole()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    // SetConsoleCP(CP_UTF8);
#endif
}

void ClearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void PauseConsole()
{
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
