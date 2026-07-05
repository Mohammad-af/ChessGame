cmake_minimum_required(VERSION 3.10)
project(ChessGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
file(GLOB SOURCES
    "src/*.cpp"
    "main.cpp"
)
add_executable(chess_game ${SOURCES}
    include/Console.hpp
    src/Console.cpp
)