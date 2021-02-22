#ifndef BOARD_H
#define BOARD_H

#define BOARD_SIZE	8

#include "Piece.h"
#include <memory>

namespace Chess {
	class Board {
	private:
		std::unique_ptr<Piece> board[BOARD_SIZE][BOARD_SIZE];

	public:
		Board() {
			//todo init all pieces on board
		}

		bool isEmpty(int row, int col) {
			return board[row][col] == nullptr;
		}

		void EatPiece( int col, int row) {
			board[col][row] = nullptr;
		}

		Color getColor(int col, int row) {
			return board[col][row]->getColor();
		}




		

	};
}

#endif // !BOARD_H