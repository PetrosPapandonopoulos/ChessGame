#include "Board.h"
#include "Queen.h"
#include <vector>


Chess::MoveResponse Chess::Queen::checkMove(int newCol, int newRow, const Board& board) {
	/* A vector used to store all the possible moves a pawn can make
	*based on its current cordinates*/
	std::vector<std::pair<int, int>> validCordinates;

	//vertical check
	addSlidingMovesHorVer(validCordinates, currentCol + 1, 8, board, true);
	addSlidingMovesHorVer(validCordinates, currentCol - 1, 0, board, true);
	//horizontal check
	addSlidingMovesHorVer(validCordinates, currentRow + 1, 8, board, false);
	addSlidingMovesHorVer(validCordinates, currentRow - 1, 0, board, false);

	//diagonal check
	addSlidingMovesDiagonal(validCordinates, { -1, -1 }, board);
	addSlidingMovesDiagonal(validCordinates, { +1, +1 }, board);
	addSlidingMovesDiagonal(validCordinates, { -1, +1 }, board);
	addSlidingMovesDiagonal(validCordinates, { +1, -1 }, board);

	return checkIfBelongs(validCordinates, { newCol, newRow }, board);
}



void Chess::Queen::addSlidingMovesHorVer(std::vector<std::pair<int, int>> validCordinates, int start, int end, const Board& board, bool checkCol) {
	bool result;
	for (int i = start; i < end; i++) {
		if (checkCol)
			result = addIfValid(board, validCordinates, { i, currentRow });
		else
			result = addIfValid(board, validCordinates, { currentCol, i });
		//if we found an enemy or friendly piece, return
		if (!result) {
			return;
		}
	}
}

void Chess::Queen::addSlidingMovesDiagonal(std::vector<std::pair<int, int>> validCordinates, std::pair<int, int> direction, const Board& board) {
	int toBeCheckedCol = this->currentCol + direction.first;
	int toBeCheckedRow = this->currentRow + direction.second;
	bool result;

	while ((toBeCheckedCol >= 0 && toBeCheckedCol <= 7) && (toBeCheckedRow >= 0 && toBeCheckedRow <= 7)) {
		result = addIfValid(board, validCordinates, { toBeCheckedCol, toBeCheckedRow });
		toBeCheckedCol += direction.first;
		toBeCheckedRow += direction.second;
		//if we found an enemy or friendly piece, return
		if (!result) {
			return;
		}
	}
}