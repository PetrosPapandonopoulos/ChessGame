#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

namespace Chess {
	
	class Board;

	class Rook: public Piece {
	protected:
		void addSlidingMoves(std::vector<std::pair<int, int>>& validCordinates, int start, int end, int dir, const Board& board, bool checkRow);
	public:
		Rook(Color color, int currentCol, int currentRow, int numOfSprite): Piece(color, currentCol, currentRow, numOfSprite) {}

		MoveResponse checkMove(int newCol, int newRow, const Board& board);
	};
}

#endif //!ROOK_H
