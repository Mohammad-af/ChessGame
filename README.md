# Chess Game

A console-based chess game developed in modern C++ with a focus on object-oriented design and clean architecture.

**GitHub Repository:** https://github.com/Mohammad-af/ChessGame

## Features

- ✅ Complete chess move validation
- ♔ Check and checkmate detection
- ♚ Stalemate detection
- ♜ Castling
- ♙ En passant
- ♕ Pawn promotion
- 🔄 Fifty-move rule
- 🔁 Threefold repetition rule
- 💾 Auto save and load game
- ♖ Unicode chess pieces
- 🖥️ Cross-platform console support
- 🧩 Object-oriented design

## Development Tools

- Git for version control
- GitHub for source code hosting and project management
- CMake for cross-platform build configuration

## Requirements

- C++17 compatible compiler
- CMake 3.10 or later

### Build with CMake

```bash
cmake -B build
cmake --build build
```

## Project Structure

```text
Chess_Project/
├── include/
│   ├── Bishop.hpp
│   ├── Board.hpp
│   ├── Console.hpp
│   ├── Display.hpp
│   ├── Game.hpp
│   ├── King.hpp
│   ├── Knight.hpp
│   ├── Move.hpp
│   ├── Pawn.hpp
│   ├── Piece.hpp
│   ├── Queen.hpp
│   └── Rook.hpp
├── src/
│   ├── Bishop.cpp
│   ├── Board.cpp
│   ├── Console.cpp
│   ├── Display.cpp
│   ├── Game.cpp
│   ├── King.cpp
│   ├── Knight.cpp
│   ├── Move.cpp
│   ├── Pawn.cpp
│   ├── Piece.cpp
│   ├── Queen.cpp
│   └── Rook.cpp
├── CMakeLists.txt
├── main.cpp
└── README.md
```

### Run

Run the generated executable from the `build` directory.

### Using an IDE

The project can be opened with any IDE that supports CMake, including:

- Visual Studio
- Visual Studio Code
- CLion

Configure CMake, build the project, and run the generated executable.

## Project Architecture

The project follows an object-oriented design where each class is responsible for a specific part of the game.

| Class | Responsibility |
|-------|----------------|
| `Game` | logic of the game, turn management, game state detection, game results(win,draw), and save/load functionality. |
| `Board` | Stores the board, executes moves, validates positions, detects attacks, and manages board state. |
| `Piece` | Abstract base class for all chess pieces. |
| `Pawn`, `Rook`, `Knight`, `Bishop`, `Queen`, `King` | Implement the movement rules for each chess piece. |
| `Move` | Represents a chess move and stores information required for move execution and undo. |
| `Display` | Renders the chessboard in the console. |
| `Console` | Provides console configuration and Unicode support. |

## External Libraries

This project does not use any third-party libraries.

Only the C++ Standard Library and CMake are required.

## License

This project is intended for learning, and educational purposes.