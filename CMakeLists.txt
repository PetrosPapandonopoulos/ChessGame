cmake_minimum_required(VERSION 3.17)
project(ChessGame)

set(CMAKE_CXX_STANDARD 14)

set(SFML_INCLUDE_DIR "SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "SFML-2.5.1/lib")
set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)
find_package(SFML 2.5.1 COMPONENTS system window audio graphics)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(ChessGame
        "src/Pieces/Bishop.cpp"
        "src/Pieces/Bishop.h"
        "src/Board.cpp"
        "src/Board.h"
        "src/Pieces/Horse.cpp"
        "src/Pieces/Horse.h"
        "src/Pieces/King.cpp"
        "src/Pieces/King.h"
        "src/main.cpp"
        "src/Pieces/Pawn.cpp"
        "src/Pieces/Pawn.h"
        "src/Pieces/Piece.cpp"
        "src/Pieces/Piece.h"
        "src/Pieces/Queen.cpp"
        "src/Pieces/Queen.h"
        "src/Pieces/Rook.cpp"
        "src/Pieces/Rook.h" src/WindowManager.cpp src/WindowManager.h)

target_link_libraries(ChessGame sfml-graphics sfml-audio sfml-window sfml-system)
