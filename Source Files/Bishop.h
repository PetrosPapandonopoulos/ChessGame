#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

namespace Chess {

	class Board;

	class Bishop : public Piece {
	protected:
		void addSlidingMoves(std::vector<std::pair<int, int>>& validCordinates, std::pair<int, int> direction, const Board& board);
	public:
		Bishop(Color color, int currentCol, int currentRow, int numOfSprite) : Piece(color, currentCol, currentRow, numOfSprite) {}

		MoveResponse checkMove(int newCol, int newRow, const Board& board);
	};

}

#endif // !BISHOP_H
