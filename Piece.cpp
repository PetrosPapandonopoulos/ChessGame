#include "Piece.h"
#include "Board.h"

Chess::Piece::Piece(Color color, int currentCol, int currentRow, int numOfSprite) :
	color(color), currentCol(currentCol), currentRow(currentRow), numOfSprite(numOfSprite) {
}

/* The checkIfValid method is used in all classes children of Piece,
* so as to determine if a piece can go to the coordinates it gets as a parameter.
* It returns true only if the cordinates, points at an empty tile*/
bool Chess::Piece::addIfValid(const Board& board, std::vector<std::pair<int, int>>& validCordinates, std::pair<int, int>cordinates) {

	if (board.isEmpty(cordinates.first, cordinates.second)) {
		validCordinates.push_back({ cordinates.first, cordinates.second });
		return true;
	}
	else if (board.getColor(cordinates.first, cordinates.second) != this->color) {
		validCordinates.push_back({ cordinates.first, cordinates.second });
		return false;
	}
	else {
		return false;
	}
}