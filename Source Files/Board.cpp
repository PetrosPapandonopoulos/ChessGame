#include "Board.h"
#include "Rook.h"
#include "Pawn.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Horse.h"
#include <algorithm>

using namespace Chess;

Board::Board() {
    //Black pieces

    //Rook
    board[0][0] = std::move(std::unique_ptr<Piece>(new Rook(Color::Black, 0, 0, 0, Type::Rook)));
    //Horse
    board[0][1] = std::move(std::unique_ptr<Piece>(new Horse(Color::Black, 0, 1, 1, Type::Horse)));
    //Bishop
    board[0][2] = std::move(std::unique_ptr<Piece>(new Bishop(Color::Black, 0, 2, 2, Type::Bishop)));
    //Queen
    board[0][3] = std::move(std::unique_ptr<Piece>(new Queen(Color::Black, 0, 3, 3, Type::Queen)));
    //King
    board[0][4] = std::move(std::unique_ptr<Piece>(new King(Color::Black, 0, 4, 4, Type::King)));
    //Bishop 2
    board[0][5] = std::move(std::unique_ptr<Piece>(new Bishop(Color::Black, 0, 5, 5, Type::Bishop)));
    //Horse 2
    board[0][6] = std::move(std::unique_ptr<Piece>(new Horse(Color::Black, 0, 6, 6, Type::Horse)));
    //Rook 2
    board[0][7] = std::move(std::unique_ptr<Piece>(new Rook(Color::Black, 0, 7, 7, Type::Rook)));

    //Pawns
    for (int i = 0; i < 8; i++) {
        board[1][i] = std::move(std::unique_ptr<Piece>(new Pawn(Color::Black, 1, i, i + 8, Type::Pawn)));
    }

    //Black pieces

    //Rook
    board[7][0] = std::move(std::unique_ptr<Piece>(new Rook(Color::White, 7, 0, 16, Type::Rook)));
    //Horse
    board[7][1] = std::move(std::unique_ptr<Piece>(new Horse(Color::White, 7, 1, 17, Type::Horse)));
    //Bishop
    board[7][2] = std::move(std::unique_ptr<Piece>(new Bishop(Color::White, 7, 2, 18, Type::Bishop)));
    //Queen
    board[7][3] = std::move(std::unique_ptr<Piece>(new Queen(Color::White, 7, 3, 19, Type::Queen)));
    //King
    board[7][4] = std::move(std::unique_ptr<Piece>(new King(Color::White, 7, 4, 20, Type::King)));
    //Bishop 2
    board[7][5] = std::move(std::unique_ptr<Piece>(new Bishop(Color::White, 7, 5, 21, Type::Bishop)));
    //Horse 2
    board[7][6] = std::move(std::unique_ptr<Piece>(new Horse(Color::White, 7, 6, 22, Type::Horse)));
    //Rook 2
    board[7][7] = std::move(std::unique_ptr<Piece>(new Rook(Color::White, 7, 7, 23, Type::Rook)));

    for (int i = 0; i < 8; i++) {
        board[6][i] = std::move(std::unique_ptr<Piece>(new Pawn(Color::White, 6, i, i + 24, Type::Pawn)));
    }

    turnFor = Color::White;
}

bool Board::move(int currentCol, int currentRow, int newCol, int newRow) {

    if (board[currentCol][currentRow] != nullptr) {

        MoveResponse result = board[currentCol][currentRow]->checkMove(newCol, newRow, *this);

        if (result == MoveResponse::Ate) {
            std::unique_ptr<Piece> pieceEaten = std::move(this->board[newCol][newRow]);

            this->board[newCol][newRow] = std::move(this->board[currentCol][currentRow]);
            board[currentCol][currentRow] = nullptr;
            board[newCol][newRow]->setCurrentCol(newCol);
            board[newCol][newRow]->setCurrentRow(newRow);

            //todo checkingForCheckers function
            Color enemyColor = turnFor == Color::White ? Color::Black : Color::White;
            if (checkingForChecks(enemyColor)) {
                this->unMove(currentCol, currentRow, newCol, newRow, pieceEaten);
                return false;
            }
            return true;
        } else if (result == MoveResponse::Moved) {
            this->board[newCol][newRow] = std::move(this->board[currentCol][currentRow]);
            this->board[currentCol][currentRow] = nullptr;
            this->board[newCol][newRow]->setCurrentCol(newCol);
            this->board[newCol][newRow]->setCurrentRow(newRow);

            //todo checkingForCheckers function
            Color enemyColor = turnFor == Color::White ? Color::Black : Color::White;
            if (checkingForChecks(enemyColor)) {
                this->unMove(currentCol, currentRow, newCol, newRow);
                return false;
            }
            return true;
        }
    }
    return false;
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

bool Board::checkingForChecks(Color teamColor) {

    std::vector<std::pair<int, int>> validCoordinates;
    std::pair<int, int> kingCoordinates;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != nullptr) {
                if (board[i][j]->getColor() != teamColor) {
                    if (board[i][j]->getPieceName() == Type::King) {
                        kingCoordinates.first = i;
                        kingCoordinates.second = j;
                    }
                } else {
                    board[i][j]->getAllPossibleMoves(validCoordinates, *this);
                }
            }
        }
    }

    auto it = std::find(validCoordinates.begin(), validCoordinates.end(), kingCoordinates);

    if (it != validCoordinates.end()) {
        return true;
    } else {
        return false;
    }
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

Color Board::getWhoseTurn() const {
    return turnFor;
}

void Board::nextTurn() {
    turnFor = turnFor == Color::White ? Color::Black : Color::White;
}

