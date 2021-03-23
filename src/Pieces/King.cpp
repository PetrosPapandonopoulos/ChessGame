#include "../Board.h"
#include "King.h"
#include <vector>

using namespace Chess;

MoveResponse King::checkMove(int newCol, int newRow, const Board &board) {
    /* A vector used to store all the possible moves a pawn can make
    *based on its current coordinates*/
    std::vector<std::pair<int, int>> validCoordinates;
    
    std::vector<std::pair<int, int>> specialValidCoordinates;
    
    getAllPossibleMoves(validCoordinates, board);
    
    checkCastling(specialValidCoordinates, board);
    
    MoveResponse normalMoves = checkIfBelongs(validCoordinates, {newCol, newRow}, board);
    
    MoveResponse castlingMoves = checkIfBelongs(specialValidCoordinates, {newCol, newRow}, board);
    
    if (normalMoves == MoveResponse::Moved || normalMoves == MoveResponse::Ate){
        return normalMoves;
    }
    else if (castlingMoves == MoveResponse::Moved){
        if (newRow == 2){
            return MoveResponse::QueenSideCastling;
        }
        else{
            return MoveResponse::KingSideCastling;
        }
    }
    return MoveResponse::Failed;
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
    
    
    int ColBasedOnColor = this->getColor() == Color::Black ? 0 : 7;
    
    if (!hasMoved) {
        if (!board.getHasMoved(ColBasedOnColor, 0)) {
            if (board.isEmpty(ColBasedOnColor, 1) && board.isEmpty(ColBasedOnColor, 2) &&
                board.isEmpty(ColBasedOnColor, 3)) {
                validCoordinates.emplace_back(ColBasedOnColor, 2);
            }
        }
        
        if (!board.getHasMoved(ColBasedOnColor, 7)){
            if (board.isEmpty(ColBasedOnColor, 5) && board.isEmpty(ColBasedOnColor, 6)) {
                validCoordinates.emplace_back(ColBasedOnColor, 6);
            }
        }
    }
}

// todo: extra valid move for king named "Castling"