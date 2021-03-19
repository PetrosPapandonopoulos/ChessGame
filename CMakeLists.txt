cmake_minimum_required(VERSION 3.17)
project(ChessGame)

set(CMAKE_CXX_STANDARD 14)

set(SFML_INCLUDE_DIR "SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "SFML-2.5.1/lib")
set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(ChessGame
        "Source Files/Bishop.cpp"
        "Source Files/Bishop.h"
        "Source Files/Board.cpp"
        "Source Files/Board.h"
        "Source Files/Horse.cpp"
        "Source Files/Horse.h"
        "Source Files/King.cpp"
        "Source Files/King.h"
        "Source Files/Main.cpp"
        "Source Files/Pawn.cpp"
        "Source Files/Pawn.h"
        "Source Files/Piece.cpp"
        "Source Files/Piece.h"
        "Source Files/Queen.cpp"
        "Source Files/Queen.h"
        "Source Files/Rook.cpp"
        "Source Files/Rook.h")

target_link_libraries(ChessGame sfml-graphics sfml-window sfml-system)
