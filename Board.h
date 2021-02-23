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

		bool move(int currentCol, int CurrentRow, int newCol, int newRow) {
			if (board[currentCol][CurrentRow] != nullptr) {
				Chess::MoveResponse result = board[CurrentRow][CurrentRow]->checkMove(newCol, newRow, *this);
				if (result == Chess::MoveResponse::Ate || result == Chess::MoveResponse::Moved) {
					board[newCol][newRow] = nullptr;
					board[newCol][newRow] = std::move(board[CurrentRow][CurrentRow]);
					board[currentCol][CurrentRow] = nullptr;
				}
			}
		}

		bool isEmpty(int row, int col) const {
			return board[row][col] == nullptr;
		}

		void EatPiece(int col, int row) {
			board[col][row] = nullptr;
		}

		Color getColor(int col, int row) const {
			return board[col][row]->getColor();
		}






	};
}

#endif // !BOARD_H