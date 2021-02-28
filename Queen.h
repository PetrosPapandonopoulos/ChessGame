#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

namespace Chess {

	class Board;

	class Queen : public Piece {
	public:
		Queen(Color color, int currentCol, int currentRow, int numOfSprite) : Piece(color, currentCol, currentRow, numOfSprite) {}

		MoveResponse checkMove(int newCol, int newRow, const Board& board) {
			return Chess::MoveResponse::Ate;
		}
	};

}

#endif // !QUEEN_H

