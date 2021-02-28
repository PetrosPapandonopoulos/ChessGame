#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

namespace Chess {
	
	class Board;

	class Rook: public Piece {
	public:
		Rook(Color color, int currentCol, int currentRow, int numOfSprite): Piece(color, currentCol, currentRow, numOfSprite)
		{ }

		MoveResponse checkMove(int newCol, int newRow, const Board& board);

	};
}

#endif