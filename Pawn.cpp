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

	if (isAtStart)
		addIfValid(board, validCordinates, { currentCol + (2 * direction), currentRow });

	addIfValid(board, validCordinates, { currentCol + (1 * direction), currentRow });
	addIfValid(board, validCordinates, { currentCol + (1 * direction), currentRow + 1 });
	addIfValid(board, validCordinates, { currentCol + (1 * direction), currentRow - 1 });

	//Create a pair to compare with the validCordinates pairs
	std::pair<int, int> inputCordinates(newCol, newRow);

	//Check if the user cordinates matches any of the validCordinates
	auto it = std::find(validCordinates.begin(), validCordinates.end(), inputCordinates);

	if (it != validCordinates.end()) {
		return !board.isEmpty(newCol, newRow) ? MoveResponse::Ate : MoveResponse::Moved;
	}
	else {
		return MoveResponse::Failed;
	}
}