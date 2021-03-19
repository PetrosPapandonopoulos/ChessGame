#include "Board.h"
#include "Bishop.h"
#include <vector>

using namespace Chess;

MoveResponse Bishop::checkMove(int newCol, int newRow, const Board &board) {

    /* A vector used to store all the possible moves a pawn can make
    *based on its current coordinates*/
    std::vector<std::pair<int, int>> validCoordinates;

    addSlidingMoves(validCoordinates, {-1, -1}, board);
    addSlidingMoves(validCoordinates, {+1, +1}, board);
    addSlidingMoves(validCoordinates, {-1, +1}, board);
    addSlidingMoves(validCoordinates, {+1, -1}, board);

    return checkIfBelongs(validCoordinates, {newCol, newRow}, board);
}

void Bishop::addSlidingMoves(std::vector<std::pair<int, int>> &validCoordinates, std::pair<int, int> direction,
                             const Board &board) {
    int toBeCheckedCol = this->currentCol + direction.first;
    int toBeCheckedRow = this->currentRow + direction.second;
    bool result;

    while ((toBeCheckedCol >= 0 && toBeCheckedCol <= 7) && (toBeCheckedRow >= 0 && toBeCheckedRow <= 7)) {
        result = addIfValid(board, validCoordinates, {toBeCheckedCol, toBeCheckedRow});
        toBeCheckedCol += direction.first;
        toBeCheckedRow += direction.second;
        if (!result) {
            return;
        }
    }
}

