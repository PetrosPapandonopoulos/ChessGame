#include "Board.h"
#include "Bishop.h"
#include <vector>

Chess::MoveResponse Chess::Bishop::checkMove(int newCol, int newRow, const Board& board) {

	/* A vector used to store all the possible moves a pawn can make
	*based on its current cordinates*/
	std::vector<std::pair<int, int>> validCordinates;

	addSlidingMoves(validCordinates, { -1, -1 }, board);
	addSlidingMoves(validCordinates, { +1, +1 }, board);
	addSlidingMoves(validCordinates, { -1, +1 }, board);
	addSlidingMoves(validCordinates, { +1, -1 }, board);

	return checkIfBelongs(validCordinates, { newCol, newRow }, board);
}

void Chess::Bishop::addSlidingMoves(std::vector<std::pair<int, int>> validCordinates, std::pair<int, int> direction, const Board& board) {
	int toBeCheckedCol = this->currentCol + direction.first;
	int toBeCheckedRow = this->currentRow + direction.second;
	bool result;

	while ((toBeCheckedCol >= 0 && toBeCheckedCol <= 7) && (toBeCheckedRow >= 0 && toBeCheckedRow <= 7)) {
		result = addIfValid(board, validCordinates, { toBeCheckedCol, toBeCheckedRow });
		toBeCheckedCol += direction.first;
		toBeCheckedRow += direction.second;
		if (!result) {
			return;
		}
	}
}

