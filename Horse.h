#ifndef HORSE_H
#define HORSE_H

#include "Piece.h"

namespace Chess {

	class Board;

	class Horse : public Piece {

	public:
		Horse(Color color, int currentCol, int currentRow, int numOfSprite) : Piece(color, currentCol, currentRow, numOfSprite) {}

		MoveResponse checkMove(int newCol, int newRow, const Board& board);
	};

}

#endif // !HORSE_H
