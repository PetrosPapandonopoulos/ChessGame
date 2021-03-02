#include "Board.h"
#include "Horse.h"
#include <vector>

Chess::MoveResponse Chess::Horse::checkMove(int newCol, int newRow, const Board& board) {

	/* A vector used to store all the possible moves a pawn can make
	*based on its current cordinates*/
	std::vector<std::pair<int, int>> validCordinates;

	//vertical check
	addHopMoves(validCordinates, this->currentCol - 2, board, true);
	addHopMoves(validCordinates, this->currentCol + 2, board, true);
	//horizontal check
	addHopMoves(validCordinates, this->currentRow - 2, board, false);
	addHopMoves(validCordinates, this->currentRow + 2, board, false);

	return checkIfBelongs(validCordinates, { newCol, newRow }, board);
}


void Chess::Horse::addHopMoves(std::vector<std::pair<int, int>> validCordinates, int Direction, const Board& board, bool checkCol) {
	if (Direction >= 0 && Direction <= 7) {
		if (checkCol) {
			if (this->currentRow + 1 <= 7) {
				addIfValid(board, validCordinates, { Direction, this->currentRow + 1 });
			}
			if (this->currentRow - 1 >= 0) {
				addIfValid(board, validCordinates, { Direction, this->currentRow - 1 });
			}
		}
		else {
			if (this->currentCol + 1 <= 7) {
				addIfValid(board, validCordinates, { this->currentCol + 1, Direction });
			}
			if (this->currentCol - 1 >= 0) {
				addIfValid(board, validCordinates, { this->currentCol - 1, Direction });
			}
		}
	}
}