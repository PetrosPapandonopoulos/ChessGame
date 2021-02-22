#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

namespace Chess {

	class Board;

	class Pawn: public Piece {
	public:
		Pawn(Color color, int currentCol, int currentRow): Piece(color, currentCol, currentRow)
		{ }

		MoveResponse checkMove(int newCol, int newRow,const Board& board);

	};
}

#endif PAWN_H
