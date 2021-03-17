#include "Board.h"
#include "King.h"
#include <vector>

Chess::MoveResponse Chess::King::checkMove(int newCol, int newRow, const Board& board) {
	/* A vector used to store all the possible moves a pawn can make
	*based on its current cordinates*/
	std::vector<std::pair<int, int>> validCordinates;

	addIfValid(board, validCordinates, { this->currentCol + 1, this->currentRow });
	addIfValid(board, validCordinates, { this->currentCol, this->currentRow + 1});
	addIfValid(board, validCordinates, { this->currentCol - 1, this->currentRow });
	addIfValid(board, validCordinates, { this->currentCol, this->currentRow - 1 });

	return checkIfBelongs(validCordinates, { newCol, newRow }, board);
}