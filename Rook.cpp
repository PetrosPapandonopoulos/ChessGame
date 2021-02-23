#include "Board.h"
#include "Rook.h"

Chess::MoveResponse Chess::Rook::checkMove(int newCol, int newRow, const Board& board) {

	enum  Direction {
		Up = -1,
		Down = +1,
		Forward = +1,
		Backward = -1
	}; 

	Direction dir;

	if (currentCol > newCol) {
		dir = Up;
	}
	else if (currentCol < newCol) {
		dir = Down;
	}
	else if (currentRow > newRow) {
		dir = Backward;
	}
	else if (currentRow < newRow) {
		dir = Forward;
	}

	//horizontal
	if (dir == Up || dir == Down) {
		for (int i = currentCol; i < newCol + (dir * -1); i++) {
			int k = currentCol + (i * dir);
			if (!board.isEmpty(k, newRow)) {
				return Chess::MoveResponse::Failed;
			}
		}
	}
	//vertical
	else if (dir == Forward || dir == Backward) {
		for (int i = currentRow; i < newCol + (dir * -1); i++) {
			int k = currentRow + (i * dir);
			if (!board.isEmpty(newCol, k)) {
				return Chess::MoveResponse::Failed;
			}
		}
	}

	//last tile
	if (!board.isEmpty(newCol, newRow)) {
		if (board.getColor(newCol, newRow) != color) {
			return Chess::MoveResponse::Ate;
		}
	}
	else {
		return Chess::MoveResponse::Moved;
	}
}