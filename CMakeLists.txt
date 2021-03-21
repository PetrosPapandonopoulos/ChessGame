cmake_minimum_required(VERSION 3.17)
project(ChessGame)

set(CMAKE_CXX_STANDARD 14)

set(SFML_INCLUDE_DIR "SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "SFML-2.5.1/lib")
set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)
find_package(SFML 2.5.1 COMPONENTS system window graphics)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(ChessGame
        "src/Bishop.cpp"
        "src/Bishop.h"
        "src/Board.cpp"
        "src/Board.h"
        "src/Horse.cpp"
        "src/Horse.h"
        "src/King.cpp"
        "src/King.h"
        "src/Main.cpp"
        "src/Pawn.cpp"
        "src/Pawn.h"
        "src/Piece.cpp"
        "src/Piece.h"
        "src/Queen.cpp"
        "src/Queen.h"
        "src/Rook.cpp"
        "src/Rook.h")

target_link_libraries(ChessGame sfml-graphics sfml-window sfml-system)
