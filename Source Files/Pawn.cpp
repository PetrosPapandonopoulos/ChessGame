#include "Board.h"
#include "Pawn.h"
#include <vector>

using namespace Chess;

MoveResponse Pawn::checkMove(int newCol, int newRow, const Board &board) {

    /* A vector used to store all the possible moves a pawn can make
    *based on its current coordinates*/
    std::vector<std::pair<int, int>> validCoordinates;

    /* Based on color a direction value is used to determine the index
    *of the forward tiles below*/
    int direction = this->color == Color::Black ? 1 : -1;

    bool hasNotMoved = this->currentCol == 1 || this->currentCol == 6;

    if (board.isEmpty(currentCol + (1 * direction), currentRow)) {

        addIfValid(board, validCoordinates, {currentCol + (1 * direction), currentRow});

        if (hasNotMoved && board.isEmpty(currentCol + (2 * direction), currentRow)) {
            if (board.isEmpty(currentCol + (2 * direction), currentRow)) {
                addIfValid(board, validCoordinates, {currentCol + (2 * direction), currentRow});
            }
        }
    }

    if (!board.isEmpty(currentCol + (1 * direction), currentRow + 1)) {
        addIfValid(board, validCoordinates, {currentCol + (1 * direction), currentRow + 1});
    }

    if (!board.isEmpty(currentCol + (1 * direction), currentRow - 1)) {
        addIfValid(board, validCoordinates, {currentCol + (1 * direction), currentRow - 1});
    }

    return checkIfBelongs(validCoordinates, {newCol, newRow}, board);
}