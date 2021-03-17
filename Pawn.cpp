#include "Board.h"
#include "Pawn.h"
#include <vector>

Chess::MoveResponse Chess::Pawn::checkMove(int newCol, int newRow, const Board& board) {

	/* A vector used to store all the possible moves a pawn can make
	*based on its current cordinates*/
	std::vector<std::pair<int, int>> validCordinates;

	/* Based on color a direction value is used to determine the index
	*of the forward tiles below*/
	int direction = this->color == Color::Black ? 1 : -1;

	bool isAtStart = this->currentCol == 1 || this->currentCol == 6;

	if (addIfValid(board, validCordinates, { currentCol + (1 * direction), currentRow }) && isAtStart) {
		if (board.isEmpty(currentCol + (2 * direction), currentRow)) {
			addIfValid(board, validCordinates, { currentCol + (2 * direction), currentRow });
		}
	}

	if (!board.isEmpty(currentCol + (1 * direction), currentRow + 1)) {
		addIfValid(board, validCordinates, { currentCol + (1 * direction), currentRow + 1 });
	}

	if (!board.isEmpty(currentCol + (1 * direction), currentRow - 1)) {
		addIfValid(board, validCordinates, { currentCol + (1 * direction), currentRow - 1 });
	}

	return checkIfBelongs(validCordinates, { newCol, newRow }, board);
}