#include "Board.h"
#include "Rook.h"
#include <vector>

// todo: extra valid move for rook named "Castling"
Chess::MoveResponse Chess::Rook::checkMove(int newCol, int newRow, const Board& board) {

	/* A vector used to store all the possible moves a pawn can make
	*based on its current cordinates*/

	std::vector<std::pair<int, int>> validCordinates;

	//vertical check
	addSlidingMoves(validCordinates, currentCol + 1, 8, board, true);
	addSlidingMoves(validCordinates, currentCol - 1, 0, board, true);
	//horizontal check
	addSlidingMoves(validCordinates, currentRow + 1, 8, board, false);
	addSlidingMoves(validCordinates, currentRow - 1, 0, board, false);

	//Create a pair to compare with the validCordinates pairs
	std::pair<int, int> inputCordinates(newCol, newRow);

	auto it = std::find(validCordinates.begin(), validCordinates.end(), inputCordinates);

	if (it != validCordinates.end()) {
		return !board.isEmpty(newCol, newRow) ? MoveResponse::Ate : MoveResponse::Moved;
	}
	else {
		return MoveResponse::Failed;
	}
}


void Chess::Rook::addSlidingMoves(std::vector<std::pair<int, int>> validCordinates, int start, int end, const Board& board, bool checkCol) {
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