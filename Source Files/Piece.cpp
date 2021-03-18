#include "Piece.h"
#include "Board.h"

using namespace Chess;

Piece::Piece(Color color, int currentCol, int currentRow, int numOfSprite) :
	color(color), currentCol(currentCol), currentRow(currentRow), numOfSprite(numOfSprite) {
}

/* The checkIfValid method is used in all classes children of Piece,
* so as to determine if a piece can go to the coordinates it gets as a parameter.
* It returns true only if the cordinates, points at an empty tile*/
bool Piece::addIfValid(const Board& board, std::vector<std::pair<int, int>>& validCordinates, std::pair<int, int>cordinates) {
	if ((cordinates.first >= 0 && cordinates.first <= 7) && (cordinates.second >= 0 && cordinates.second <= 7)) {
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
	return false;
}

Chess::MoveResponse Piece::checkIfBelongs(std::vector<std::pair<int, int>> validCordinates, std::pair<int, int> inputCordinates, const Board& board) {

	auto it = std::find(validCordinates.begin(), validCordinates.end(), inputCordinates);

	if (it != validCordinates.end()) {
		return !board.isEmpty(inputCordinates.first, inputCordinates.second) ? MoveResponse::Ate : MoveResponse::Moved;
	}
	else {
		return MoveResponse::Failed;
	}
}