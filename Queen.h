#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

namespace Chess {

	class Board;

	class Queen : public Piece {
	private:
		void addSlidingMovesHorVer(std::vector<std::pair<int, int>> validCordinates, int start, int end, const Board& board, bool checkCol);
		void addSlidingMovesDiagonal(std::vector<std::pair<int, int>> validCordinates, std::pair<int, int> direction, const Board& board);
	public:
		Queen(Color color, int currentCol, int currentRow, int numOfSprite) : Piece(color, currentCol, currentRow, numOfSprite) {}

		MoveResponse checkMove(int newCol, int newRow, const Board& board);
	};
}

#endif // !QUEEN_H

