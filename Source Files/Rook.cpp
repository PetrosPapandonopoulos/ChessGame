#include "Board.h"
#include "Rook.h"
#include <vector>

using namespace Chess;

MoveResponse Rook::checkMove(int newCol, int newRow, const Board& board) {

	/* A vector used to store all the possible moves a pawn can make
	*based on its current cordinates*/

	std::vector<std::pair<int, int>> validCordinates;

	//horizontal check
	addSlidingMoves(validCordinates, currentCol + 1, 8, 1, board, true);
	addSlidingMoves(validCordinates, currentCol - 1, 0, -1, board, true);
	//vertical check
	addSlidingMoves(validCordinates, currentRow + 1, 8, 1, board, false);
	addSlidingMoves(validCordinates, currentRow - 1, 0, -1, board, false);

	return checkIfBelongs(validCordinates, { newCol, newRow }, board);
}


void Rook::addSlidingMoves(std::vector<std::pair<int, int>>& validCordinates, int start, int end, int dir, const Board& board, bool checkCol) {
	bool result;
	if (dir == 1) {
		for (int i = start; i < end; i += dir) {
			if (checkCol)
				result = addIfValid(board, validCordinates, { i, currentRow });
			else
				result = addIfValid(board, validCordinates, { currentCol, i });
			//if we found an enemy or friendly piece, return
			if (!result) {
				break;
			}
		}
	}
	else {
		for (int i = start; i >= end; i += dir) {
			if (checkCol)
				result = addIfValid(board, validCordinates, { i, currentRow });
			else
				result = addIfValid(board, validCordinates, { currentCol, i });
			//if we found an enemy or friendly piece, return
			if (!result) {
				break;
			}
		}
	}
}

// todo: extra valid move for rook named "Castling"