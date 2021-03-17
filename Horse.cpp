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
	
	if (checkCol) {
		addIfValid(board, validCordinates, { Direction, this->currentRow + 1 });
		addIfValid(board, validCordinates, { Direction, this->currentRow - 1 });
	}
	else {
		addIfValid(board, validCordinates, { this->currentCol + 1, Direction });
		addIfValid(board, validCordinates, { this->currentCol - 1, Direction });
	}
}