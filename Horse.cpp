#include "Board.h"
#include "Horse.h"
#include <vector>


Chess::MoveResponse Chess::Horse::checkMove(int newCol, int newRow, const Board& board) {

	/* A vector used to store all the possible moves a pawn can make
	*based on its current cordinates*/

	std::vector<std::pair<int, int>> validCordinates;

	if (this->currentCol - 2 >= 0) {
		if (this->currentRow + 1 <= 7) {
			addIfValid(board, validCordinates, { this->currentCol - 2, this->currentRow + 1 });
		}
		if (this->currentRow - 1 >= 0) {
			addIfValid(board, validCordinates, { this->currentCol - 2, this->currentRow - 1 });
		}
	}

	if (this->currentCol + 2 <= 7) {
		if (this->currentRow + 1 <= 7) {
			addIfValid(board, validCordinates, { this->currentCol + 2, this->currentRow + 1 });
		}
		if (this->currentRow - 1 >= 0) {
			addIfValid(board, validCordinates, { this->currentCol + 2, this->currentRow - 1 });
		}
	}

	if (this->currentRow - 2 >= 0) {
		if (this->currentCol + 1 <= 7) {
			addIfValid(board, validCordinates, { this->currentCol + 1, this->currentRow - 2 });
		}
		if (this->currentCol - 1 <= 0) {
			addIfValid(board, validCordinates, { this->currentCol - 1, this->currentRow - 2 });
		}
	}

	if (this->currentRow + 2 >= 0) {
		if (this->currentCol + 1 <= 7) {
			addIfValid(board, validCordinates, { this->currentCol + 1, this->currentRow + 2 });
		}
		if (this->currentCol - 1 <= 0) {
			addIfValid(board, validCordinates, { this->currentCol - 1, this->currentRow + 2 });
		}
	}

	//Create a pair to compare with the validCordinates pairs
	std::pair<int, int> inputCordinates(newCol, newRow);

	auto it = std::find(validCordinates.begin(), validCordinates.end(), inputCordinates);

	if (it != validCordinates.end()) {
		return !board.isEmpty(newCol, newRow) ? MoveResponse::Ate : MoveResponse::Moved;
	}
	else {
		return MoveResponse::Failed;
	}

	return MoveResponse::Failed;
}