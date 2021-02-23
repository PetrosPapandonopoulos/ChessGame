#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

namespace Chess {
	
	class Board;

	class Rook: public Piece {
	public:
		Rook(Color color, int currentCol, int current): Piece(color, currentCol, currentRow)
		{ }

		MoveResponse checkMove(int newCol, int newRow, const Board& board);

	};
}

#endif
