#include "Board.h"
#include "Queen.h"
#include <vector>

using namespace Chess;

MoveResponse Queen::checkMove(int newCol, int newRow, const Board &board) {
    /* A vector used to store all the possible moves a pawn can make
    *based on its current coordinates*/
    std::vector<std::pair<int, int>> validCoordinates;

    getAllPossibleMoves(validCoordinates, board);

    return checkIfBelongs(validCoordinates, {newCol, newRow}, board);
}

//to be fixed into one (the method will be written in piece)

void Queen::addSlidingMovesHorVer(std::vector<std::pair<int, int>> &validCoordinates, int start, int end, int dir,
                                  const Board &board, bool checkCol) {
    bool result;
    if (dir == 1) {
        for (int i = start; i < end; i += dir) {
            if (checkCol)
                result = addIfValid(board, validCoordinates, {i, currentRow});
            else
                result = addIfValid(board, validCoordinates, {currentCol, i});
            //if we found an enemy or friendly piece, return
            if (!result) {
                break;
            }
        }
    } else {
        for (int i = start; i >= end; i += dir) {
            if (checkCol)
                result = addIfValid(board, validCoordinates, {i, currentRow});
            else
                result = addIfValid(board, validCoordinates, {currentCol, i});
            //if we found an enemy or friendly piece, return
            if (!result) {
                break;
            }
        }
    }
}

void Queen::addSlidingMovesDiagonal(std::vector<std::pair<int, int>> &validCoordinates, std::pair<int, int> direction,
                                    const Board &board) {
    int toBeCheckedCol = this->currentCol + direction.first;
    int toBeCheckedRow = this->currentRow + direction.second;
    bool result;

    while ((toBeCheckedCol >= 0 && toBeCheckedCol <= 7) && (toBeCheckedRow >= 0 && toBeCheckedRow <= 7)) {
        result = addIfValid(board, validCoordinates, {toBeCheckedCol, toBeCheckedRow});
        toBeCheckedCol += direction.first;
        toBeCheckedRow += direction.second;
        //if we found an enemy or friendly piece, return
        if (!result) {
            return;
        }
    }
}

void Queen::getAllPossibleMoves(std::vector<std::pair<int, int>>& validCoordinates, const Board &board) {
    //vertical check
    addSlidingMovesHorVer(validCoordinates, currentCol + 1, 8, 1, board, true);
    addSlidingMovesHorVer(validCoordinates, currentCol - 1, 0, -1, board, true);
    //horizontal check
    addSlidingMovesHorVer(validCoordinates, currentRow + 1, 8, 1, board, false);
    addSlidingMovesHorVer(validCoordinates, currentRow - 1, 0, -1, board, false);

    //diagonal check
    addSlidingMovesDiagonal(validCoordinates, {-1, -1}, board);
    addSlidingMovesDiagonal(validCoordinates, {+1, +1}, board);
    addSlidingMovesDiagonal(validCoordinates, {-1, +1}, board);
    addSlidingMovesDiagonal(validCoordinates, {+1, -1}, board);
}