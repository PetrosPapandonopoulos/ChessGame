#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

namespace Chess {

	class Board;

	class Bishop : public Piece {
	public:
		Bishop(Color color, int currentCol, int currentRow, int numOfSprite) : Piece(color, currentCol, currentRow, numOfSprite) {}

		MoveResponse checkMove(int newCol, int newRow, const Board& board) {
			return Chess::MoveResponse::Ate;
		}
	};

}

#endif // !BISHOP_H
