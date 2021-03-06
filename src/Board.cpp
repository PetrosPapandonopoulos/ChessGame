#include "Pieces/Bishop.h"
#include "Pieces/Rook.h"
#include "Pieces/Pawn.h"
#include "Pieces/King.h"
#include "Pieces/Queen.h"
#include "Pieces/Horse.h"
#include "Board.h"
#include <algorithm>
#include <iostream>

using namespace Chess;

Board::Board() {
    //Black pieces
    
    //Rook
    board[0][0] = std::move(std::unique_ptr<Piece>(new Rook(Color::Black, 0, 0, 0, Type::Rook, false)));
    //Horse
    board[0][1] = std::move(std::unique_ptr<Piece>(new Horse(Color::Black, 0, 1, 1, Type::Horse, false)));
    //Bishop
    board[0][2] = std::move(std::unique_ptr<Piece>(new Bishop(Color::Black, 0, 2, 2, Type::Bishop, false)));
    //Queen
    board[0][3] = std::move(std::unique_ptr<Piece>(new Queen(Color::Black, 0, 3, 3, Type::Queen, false)));
    //King
    board[0][4] = std::move(std::unique_ptr<Piece>(new King(Color::Black, 0, 4, 4, Type::King, false)));
    //Bishop 2
    board[0][5] = std::move(std::unique_ptr<Piece>(new Bishop(Color::Black, 0, 5, 5, Type::Bishop, false)));
    //Horse 2
    board[0][6] = std::move(std::unique_ptr<Piece>(new Horse(Color::Black, 0, 6, 6, Type::Horse, false)));
    //Rook 2
    board[0][7] = std::move(std::unique_ptr<Piece>(new Rook(Color::Black, 0, 7, 7, Type::Rook, false)));
    
    //Pawns
    for (int i = 0; i < 8; i++) {
        board[1][i] = std::move(std::unique_ptr<Piece>(new Pawn(Color::Black, 1, i, i + 8, Type::Pawn, false)));
    }
    
    //Black pieces
    
    //Rook
    board[7][0] = std::move(std::unique_ptr<Piece>(new Rook(Color::White, 7, 0, 16, Type::Rook, false)));
    //Horse
    board[7][1] = std::move(std::unique_ptr<Piece>(new Horse(Color::White, 7, 1, 17, Type::Horse, false)));
    //Bishop
    board[7][2] = std::move(std::unique_ptr<Piece>(new Bishop(Color::White, 7, 2, 18, Type::Bishop, false)));
    //Queen
    board[7][3] = std::move(std::unique_ptr<Piece>(new Queen(Color::White, 7, 3, 19, Type::Queen, false)));
    //King
    board[7][4] = std::move(std::unique_ptr<Piece>(new King(Color::White, 7, 4, 20, Type::King, false)));
    //Bishop 2
    board[7][5] = std::move(std::unique_ptr<Piece>(new Bishop(Color::White, 7, 5, 21, Type::Bishop, false)));
    //Horse 2
    board[7][6] = std::move(std::unique_ptr<Piece>(new Horse(Color::White, 7, 6, 22, Type::Horse, false)));
    //Rook 2
    board[7][7] = std::move(std::unique_ptr<Piece>(new Rook(Color::White, 7, 7, 23, Type::Rook, false)));
    
    for (int i = 0; i < 8; i++) {
        board[6][i] = std::move(std::unique_ptr<Piece>(new Pawn(Color::White, 6, i, i + 24, Type::Pawn, false)));
    }
    
    turnFor = Color::White;
}

MoveResponse Board::move(int currentCol, int currentRow, int newCol, int newRow, bool pseudoMove) {
    
    if (board[currentCol][currentRow] != nullptr) {
        
        MoveResponse result = board[currentCol][currentRow]->checkMove(newCol, newRow, *this);
        
        std::pair<int, int> kingCoordinates;
        
        if (result == MoveResponse::Ate) {
            
            std::unique_ptr<Piece> pieceEaten = std::move(this->board[newCol][newRow]);
            
            moveObject(currentCol, currentRow, newCol, newRow);
            
            //todo checkingForCheckers function
            Color enemyColor = turnFor == Color::White ? Color::Black : Color::White;
            if (checkingForChecks(enemyColor, kingCoordinates)) {
                this->unMove(currentCol, currentRow, newCol, newRow, pieceEaten);
                return MoveResponse::Failed;
            }
            if (pseudoMove) {
                this->unMove(currentCol, currentRow, newCol, newRow, pieceEaten);
            }
            else {
                board[newCol][newRow]->pieceMoved();
                //en passant reset
                en_passantCord = {-1, -1};
            }
            return MoveResponse::Ate;
        }
        else if (result == MoveResponse::Moved) {
            moveObject(currentCol, currentRow, newCol, newRow);
            
            Color enemyColor = turnFor == Color::White ? Color::Black : Color::White;
            
            if (checkingForChecks(enemyColor, kingCoordinates)) {
                this->unMove(currentCol, currentRow, newCol, newRow);
                return MoveResponse::Failed;
            }
            
            if (pseudoMove) {
                this->unMove(currentCol, currentRow, newCol, newRow);
            }
            else {
                board[newCol][newRow]->pieceMoved();
                if (board[newCol][newRow]->getTimesMoved() == 1 &&
                    board[newCol][newRow]->getPieceName() == Type::Pawn) {
                    
                    en_passantCord = {newCol, newRow};
                }
                else {
                    en_passantCord = {-1, -1};
                }
            }
            
            return MoveResponse::Moved;
        }
        else if (result == MoveResponse::QueenSideCastling) {
            
            Color enemyColor = turnFor == Color::White ? Color::Black : Color::White;
            
            if (checkingForChecks(enemyColor, kingCoordinates)) {
                return MoveResponse::Failed;
            }
            
            //check first tile if its dominated
            moveObject(currentCol, currentRow, currentCol, currentRow - 1);
            int ColBasedOnColor = turnFor == Color::Black ? 0 : 7;
            
            if (checkingForChecks(enemyColor, kingCoordinates)) {
                this->unMove(currentCol, currentRow, currentCol, currentRow - 1);
                return MoveResponse::Failed;
            }
            this->unMove(currentCol, currentRow, currentCol, currentRow - 1);
            
            //check if second tile end's up in check
            moveObject(currentCol, currentRow, newCol, newRow);
            if (checkingForChecks(enemyColor, kingCoordinates)) {
                this->unMove(currentCol, currentRow, newCol, newRow);
                return MoveResponse::Failed;
            }
            
            //move Rook
            moveObject(ColBasedOnColor, 0, ColBasedOnColor, 3);
            board[newCol][newRow]->pieceMoved();
            board[ColBasedOnColor][3]->pieceMoved();
            return MoveResponse::QueenSideCastling;
        }
        else if (result == MoveResponse::KingSideCastling) {
            
            Color enemyColor = turnFor == Color::White ? Color::Black : Color::White;
            
            if (checkingForChecks(enemyColor, kingCoordinates)) {
                return MoveResponse::Failed;
            }
            
            //check first tile if its dominated
            moveObject(currentCol, currentRow, currentCol, currentRow + 1);
            
            int ColBasedOnColor = turnFor == Color::Black ? 0 : 7;
            
            if (checkingForChecks(enemyColor, kingCoordinates)) {
                this->unMove(currentCol, currentRow, currentCol, currentRow + 1);
                return MoveResponse::Failed;
            }
            this->unMove(currentCol, currentRow, currentCol, currentRow + 1);
            
            //check if second tile end's up in check
            moveObject(currentCol, currentRow, newCol, newRow);
            if (checkingForChecks(enemyColor, kingCoordinates)) {
                this->unMove(currentCol, currentRow, newCol, newRow);
                return MoveResponse::Failed;
            }
            
            //move Rook
            moveObject(ColBasedOnColor, 7, ColBasedOnColor, 5);
            board[newCol][newRow]->pieceMoved();
            board[ColBasedOnColor][5]->pieceMoved();
            return MoveResponse::KingSideCastling;
        }
        else if (result == MoveResponse::EnPassant) {
            
            if (en_passantCord.first == -1) {
                
                return MoveResponse::Failed;
            }
            
            int direction = board[currentCol][currentRow]->getColor() == Color::Black ? 1 : -1;
            Color enemyColor = turnFor == Color::White ? Color::Black : Color::White;
            
            if (en_passantCord.first == newCol - (1 * direction) && en_passantCord.second == newRow) {
                
                moveObject(currentCol, currentRow, newCol, newRow);
                std::unique_ptr<Piece> pieceEaten = std::move(board[currentCol][newRow]);
                board[currentCol][newRow] = nullptr;
                
                if (checkingForChecks(enemyColor, kingCoordinates)) {
                    
                    this->unMove(currentCol, currentRow, newCol, newRow);
                    board[currentCol][newRow] = std::move(pieceEaten);
                    return MoveResponse::Failed;
                }
                else {
                    
                    return MoveResponse::EnPassant;
                }
            }
            else if (en_passantCord.first == newCol + (1 * direction) && en_passantCord.second == newRow) {
                
                moveObject(currentCol, currentRow, newCol, newRow);
                
                std::unique_ptr<Piece> pieceEaten = std::move(board[currentCol][newRow]);
                board[currentCol][newRow] = nullptr;
                
                if (checkingForChecks(enemyColor, kingCoordinates)) {
                    
                    this->unMove(currentCol, currentRow, newCol, newRow);
                    board[currentCol][newRow] = std::move(pieceEaten);
                    return MoveResponse::Failed;
                }
                else {
                    
                    return MoveResponse::EnPassant;
                }
            }
        }
    }
    
    return MoveResponse::Failed;
}

void Board::unMove(int currentCol, int currentRow, int newCol, int newRow, std::unique_ptr<Piece> &pieceEaten) {
    this->board[currentCol][currentRow] = std::move(this->board[newCol][newRow]);
    this->board[currentCol][currentRow]->setCurrentCol(currentCol);
    this->board[currentCol][currentRow]->setCurrentRow(currentRow);
    this->board[newCol][newRow] = std::move(pieceEaten);
}

void Board::unMove(int currentCol, int currentRow, int newCol, int newRow) {
    this->board[currentCol][currentRow] = std::move(this->board[newCol][newRow]);
    this->board[currentCol][currentRow]->setCurrentCol(currentCol);
    this->board[currentCol][currentRow]->setCurrentRow(currentRow);
    this->board[newCol][newRow] = nullptr;
}

void Board::moveObject(int currentCol, int currentRow, int newCol, int newRow) {
    
    this->board[newCol][newRow] = std::move(this->board[currentCol][currentRow]);
    this->board[currentCol][currentRow] = nullptr;
    this->board[newCol][newRow]->setCurrentCol(newCol);
    this->board[newCol][newRow]->setCurrentRow(newRow);
}

bool Board::checkingForChecks(Color teamColor, std::pair<int, int> &kingCoordinates) const {
    
    std::vector<std::pair<int, int>> validCoordinates;
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != nullptr) {
                if (board[i][j]->getColor() != teamColor) {
                    if (board[i][j]->getPieceName() == Type::King) {
                        kingCoordinates.first = i;
                        kingCoordinates.second = j;
                    }
                }
                else {
                    board[i][j]->getAllPossibleMoves(validCoordinates, *this);
                }
            }
        }
    }
    
    auto it = std::find(validCoordinates.begin(), validCoordinates.end(), kingCoordinates);
    
    if (it != validCoordinates.end()) {
        return true;
    }
    else {
        return false;
    }
}

bool Board::checkForCheckmate(Color teamColor) {
    
    std::vector<std::pair<int, int>> validCoordinates;
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            validCoordinates.clear();
            if (board[i][j] != nullptr) {
                if (board[i][j]->getColor() != teamColor) {
                    board[i][j]->getAllPossibleMoves(validCoordinates, *this);
                    for (auto it = validCoordinates.begin(); it < validCoordinates.end(); it++) {
                        if (move(i, j, it->first, it->second, true) != MoveResponse::Failed) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool Board::isEmpty(int row, int col) const {
    return board[row][col] == nullptr;
}

Color Board::getColor(int col, int row) const {
    return board[col][row]->getColor();
}

int Board::getNumOfSprite(int i, int j) const {
    return board[i][j]->getNumOfSprite();
}

bool Board::getHasMoved(int col, int row) const {
    return board[col][row]->getHasMoved();
}

Color Board::getWhoseTurn() const {
    return turnFor;
}

void Board::nextTurn() {
    turnFor = turnFor == Color::White ? Color::Black : Color::White;
}

Color Board::checkForPromotion() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (!isEmpty(0, i)) {
            if (board[0][i]->getPieceName() == Type::Pawn) {
                return Color::White;
            }
        }
        if (!isEmpty(7, i)) {
            if (board[7][i]->getPieceName() == Type::Pawn) {
                return Color::Black;
            }
        }
    }
    return Color::None;
}

bool Board::promote(std::pair<int, int> pieceCoordinates, Type promoteTo) {
    if (board[pieceCoordinates.first][pieceCoordinates.second]->getPieceName() == Type::Pawn) {
        int col = pieceCoordinates.first;
        int row = pieceCoordinates.second;
        Color newColor = getColor(col, row);
        int newNumOfSprite = getNumOfSprite(col, row);
        
        switch (promoteTo) {
            case Type::Rook: {
                board[col][row] = std::move(
                        std::unique_ptr<Piece>(new Rook(newColor, col, row, newNumOfSprite, Type::Rook, false)));
                break;
            }
            case Type::Horse: {
                board[col][row] = std::move(
                        std::unique_ptr<Piece>(new Horse(newColor, col, row, newNumOfSprite, Type::Horse, false)));
                break;
            }
            case Type::Bishop: {
                board[col][row] = std::move(
                        std::unique_ptr<Piece>(new Bishop(newColor, col, row, newNumOfSprite, Type::Bishop, false)));
                break;
            }
            case Type::Queen: {
                board[col][row] = std::move(
                        std::unique_ptr<Piece>(new Queen(newColor, col, row, newNumOfSprite, Type::Queen, false)));
                break;
            }
            default: {
            
            }
        }
        return true;
    }
    else {
        std::cout << "Error" << std::endl;
        return false;
    }
}

Type Board::getPieceName(int col, int row) const {
    return board[col][row]->getPieceName();
}

void Board::getAllPossibleMoves(std::pair<int, int> index, std::vector<std::pair<int, int>> &validCoordinates) {
    this->board[index.first][index.second]->getAllPossibleMoves(validCoordinates, *this);
    if(this->board[index.first][index.second]->getPieceName() == Type::Pawn){
        Pawn *pawn = dynamic_cast<Pawn*>(this->board[index.first][index.second].get());
        pawn->getEnPassant(validCoordinates, *this);
    }
    else if(this->board[index.first][index.second]->getPieceName() == Type::King){
        King *king = dynamic_cast<King*>(this->board[index.first][index.second].get());
        king->checkCastling(validCoordinates, *this);
    }
}
