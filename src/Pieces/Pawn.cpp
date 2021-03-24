#include "../Board.h"
#include "Pawn.h"
#include <vector>

using namespace Chess;

MoveResponse Pawn::checkMove(int newCol, int newRow, const Board &board) {
    
    /* A vector used to store all the possible moves a pawn can make
    *based on its current coordinates*/
    std::vector<std::pair<int, int>> validCoordinates;
    
    std::vector<std::pair<int, int>> specialValidCoordinates;
    
    getAllPossibleMoves(validCoordinates, board);
    
    MoveResponse response = checkIfBelongs(validCoordinates, {newCol, newRow}, board);
    
    if (response != MoveResponse::Failed) {
        return response;
    }
    
    getEnPassant(specialValidCoordinates, board);
    
    response = checkIfBelongs(specialValidCoordinates, {newCol, newRow}, board);
    
    if (response == MoveResponse::Moved) {
        return MoveResponse::EnPassant;
    }
    else {
        return response;
    }
}

void Pawn::getAllPossibleMoves(std::vector<std::pair<int, int>> &validCoordinates, const Board &board) {
    /* Based on color a direction value is used to determine the index
    *of the forward tiles below*/
    int direction = this->color == Color::Black ? 1 : -1;
    
    if (board.isEmpty(currentCol + (1 * direction), currentRow)) {
        
        addIfValid(board, validCoordinates, {currentCol + (1 * direction), currentRow});
        
        if (!hasMoved && board.isEmpty(currentCol + (2 * direction), currentRow)) {
            
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
}

void Pawn::getEnPassant(std::vector<std::pair<int, int>> &validCoordinates, const Board &board) {
    /* Based on color a direction value is used to determine the index
    *of the forward tiles below*/
    int direction = this->color == Color::Black ? 1 : -1;
    
    if (currentRow >= 1) {
        if (!board.isEmpty(currentCol, currentRow - 1) &&
            board.getPieceName(currentCol, currentRow - 1) == Type::Pawn) {
            
            validCoordinates.emplace_back(currentCol + (1 * direction), currentRow - 1);
            
        }
    }
    
    if (currentRow <= 6) {
        if (!board.isEmpty(currentCol, currentRow + 1) &&
            board.getPieceName(currentCol, currentRow + 1) == Type::Pawn) {
            
            validCoordinates.emplace_back(currentCol + (1 * direction), currentRow + 1);
        }
    }
}