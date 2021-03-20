#include "Board.h"
#include "Horse.h"
#include <vector>

using namespace Chess;

MoveResponse Horse::checkMove(int newCol, int newRow, const Board &board) {

    /* A vector used to store all the possible moves a pawn can make
    *based on its current coordinates*/
    std::vector<std::pair<int, int>> validCoordinates;

    getAllPossibleMoves(validCoordinates, board);

    return checkIfBelongs(validCoordinates, {newCol, newRow}, board);
}


void Horse::addHopMoves(std::vector<std::pair<int, int>> &validCoordinates, int Direction, const Board &board,
                        bool checkCol) {

    if (checkCol) {
        addIfValid(board, validCoordinates, {Direction, this->currentRow + 1});
        addIfValid(board, validCoordinates, {Direction, this->currentRow - 1});
    } else {
        addIfValid(board, validCoordinates, {this->currentCol + 1, Direction});
        addIfValid(board, validCoordinates, {this->currentCol - 1, Direction});
    }
}

void Horse::getAllPossibleMoves(std::vector<std::pair<int, int>> &validCoordinates, const Board &board){
    //vertical check
    addHopMoves(validCoordinates, this->currentCol - 2, board, true);
    addHopMoves(validCoordinates, this->currentCol + 2, board, true);
    //horizontal check
    addHopMoves(validCoordinates, this->currentRow - 2, board, false);
    addHopMoves(validCoordinates, this->currentRow + 2, board, false);
}