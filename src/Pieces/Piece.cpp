#include <algorithm>
#include "Piece.h"
#include "../Board.h"

using namespace Chess;

Piece::Piece(Color color, int currentCol, int currentRow, int numOfSprite, Type pieceName, bool hasMoved) :
        color(color), currentCol(currentCol), currentRow(currentRow), numOfSprite(numOfSprite), pieceName(pieceName),
        hasMoved(hasMoved) {}

/* The checkIfValid method is used in all classes children of Piece,
* so as to determine if a piece can go to the coordinates it gets as a parameter.
* It returns true only if the coordinates, points at an empty tile*/
bool Piece::addIfValid(const Board &board, std::vector<std::pair<int, int>> &validCoordinates,
                       std::pair<int, int> coordinates) {
    if ((coordinates.first >= 0 && coordinates.first <= 7) && (coordinates.second >= 0 && coordinates.second <= 7)) {
        if (board.isEmpty(coordinates.first, coordinates.second)) {
            validCoordinates.emplace_back(coordinates.first, coordinates.second);
            return true;
        }
        else if (board.getColor(coordinates.first, coordinates.second) != this->color) {
            validCoordinates.emplace_back(coordinates.first, coordinates.second);
            return false;
        }
        else {
            return false;
        }
    }
    return false;
}

MoveResponse
Piece::checkIfBelongs(std::vector<std::pair<int, int>> validCoordinates, std::pair<int, int> inputCoordinates,
                      const Board &board) {
    
    auto it = std::find(validCoordinates.begin(), validCoordinates.end(), inputCoordinates);
    
    if (it != validCoordinates.end()) {
        return !board.isEmpty(inputCoordinates.first, inputCoordinates.second) ? MoveResponse::Ate
                                                                               : MoveResponse::Moved;
    }
    else {
        return MoveResponse::Failed;
    }
}

Color Piece::getColor() {
    return color;
}

Type Piece::getPieceName() {
    return pieceName;
}

void Piece::pieceMoved() {
    this->hasMoved = true;
}

bool Piece::getHasMoved() const{
    return hasMoved;
}

int Piece::getNumOfSprite() const {
    return numOfSprite;
}

void Piece::setCurrentCol(int newCol) {
    this->currentCol = newCol;
}

void Piece::setCurrentRow(int newRow) {
    this->currentRow = newRow;
}