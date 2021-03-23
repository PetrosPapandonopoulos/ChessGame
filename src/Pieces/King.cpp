#include "../Board.h"
#include "King.h"
#include <vector>

using namespace Chess;

MoveResponse King::checkMove(int newCol, int newRow, const Board &board) {
    /* A vector used to store all the possible moves a pawn can make
    *based on its current coordinates*/
    std::vector<std::pair<int, int>> validCoordinates;
    
    getAllPossibleMoves(validCoordinates, board);
    
    checkCastling(validCoordinates, board);
    
    return checkIfBelongs(validCoordinates, {newCol, newRow}, board);
}

void King::getAllPossibleMoves(std::vector<std::pair<int, int>> &validCoordinates, const Board &board) {
    addIfValid(board, validCoordinates, {this->currentCol + 1, this->currentRow});
    addIfValid(board, validCoordinates, {this->currentCol + 1, this->currentRow + 1});
    addIfValid(board, validCoordinates, {this->currentCol + 1, this->currentRow - 1});
    
    addIfValid(board, validCoordinates, {this->currentCol - 1, this->currentRow});
    addIfValid(board, validCoordinates, {this->currentCol - 1, this->currentRow + 1});
    addIfValid(board, validCoordinates, {this->currentCol - 1, this->currentRow - 1});
    
    addIfValid(board, validCoordinates, {this->currentCol, this->currentRow + 1});
    addIfValid(board, validCoordinates, {this->currentCol, this->currentRow - 1});
}

void King::checkCastling(std::vector<std::pair<int, int>> &validCoordinates, const Board &board) {
    
    std::pair<int, int> kingCoordinates;
    Color EnemyTeamColor = this->getColor() == Color::Black ? Color::White : Color::Black;
    
    if (!board.checkingForChecks(EnemyTeamColor, kingCoordinates) && !hasMoved) {
        if (this->getColor() == Color::Black){
            
        }
    }
    
}

// todo: extra valid move for king named "Castling"