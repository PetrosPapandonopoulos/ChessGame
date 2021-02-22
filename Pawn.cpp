#include "Board.h"
#include "Pawn.h"

bool Chess::Pawn::move(int newCol, int newRow, Board board) {

	//black pawn eats -> white piece
	if (color == Color::Black && (newCol == currentCol + 1) && (newRow == currentRow + 1 || newRow == currentRow - 1)) {
		if (!board.isEmpty(newCol, newRow) && board.getColor(newCol, newRow) == Color::White) {
			board.EatPiece(newCol, newRow);
			currentCol = newCol;
			currentRow = newRow;
			return true;

		}
	}

	//white pawn eats -> black piece
	if (color == Color::White && (newCol == currentCol - 1) && (newRow == currentRow + 1 || newRow == currentRow - 1)) {
		if (!board.isEmpty(newCol, newRow) && board.getColor(newCol, newRow) == Color::Black) {
			board.EatPiece(newCol, newRow);
			currentCol = newCol;
			currentRow = newRow;
			return true;

		}
	}

	//Simple move forward
	if (board.isEmpty(newCol, newRow)) {
		if (color == Color::Black) {
			if ((currentCol + 1) == newCol) {
				currentCol = newCol;
				currentRow = newRow;
				return true;
			}
			//First time two tiles move
			else if ((currentCol == 1 && newCol == 3) && (board.isEmpty(newCol - 1, newRow - 1))) {
				currentCol = newCol;
				currentRow = newRow;
				return true;
			}
		}
		else if (color == Color::White) {
			if (currentCol - 1 == newCol) {
				currentCol = newCol;
				currentRow = newRow;
				return true;
			}
			//First time two tiles move
			else if ((currentCol == 6 &&  newCol == 4) && (board.isEmpty(newCol + 1, newRow + 1))) {
				currentCol = newCol;
				currentRow = newRow;
				return true;
			}
		}
	}

	return false;
}





