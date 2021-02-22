#include "Board.h"
#include "Pawn.h"


Chess::MoveResponse Chess::Pawn::checkMove(int newCol, int newRow,const Board& board) {

	//Ate
	if( (newCol == currentCol + 1 && this->color == Color::Black) ||
		(newCol == currentCol - 1 && this->color == Color::White) &&
		(newRow == currentRow + 1 || newRow == currentRow - 1)) {
		if (!board.isEmpty(newCol, newRow) && board.getColor(newCol, newRow) != this->color) {
			return Chess::MoveResponse::Ate;
		}
	}

	//Moved
	if (board.isEmpty(newCol, newRow)) {
		if (color == Color::Black) {
			if ((currentCol + 1) == newCol || ((currentCol == 1 && newCol == 3)) && (board.isEmpty(newCol - 1, newRow - 1))) {
				return Chess::MoveResponse::Moved;
			}
		}
		else if (color == Color::White) {
			if (currentCol - 1 == newCol || ((currentCol == 6 && newCol == 4) && (board.isEmpty(newCol + 1, newRow + 1)))) {
				return Chess::MoveResponse::Moved;
			}
		}
	}

	//Failed
	return Chess::MoveResponse::Failed;
}