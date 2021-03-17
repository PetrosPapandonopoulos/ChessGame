#ifndef BOARD_H
#define BOARD_H
#define BOARD_SIZE	8

#include "Piece.h"
#include "Rook.h"
#include "Pawn.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Horse.h"
#include <memory>

namespace Chess {
	class Board {

	public:
		std::unique_ptr<Piece> board[BOARD_SIZE][BOARD_SIZE];

		Board() {
			//Black pieces

			//Rook
			board[0][0] = std::move(std::unique_ptr<Piece>(new Rook(Color::Black, 0, 0, 0)));
			//Horse
			board[0][1] = std::move(std::unique_ptr<Piece>(new Horse(Color::Black, 0, 1, 1)));
			//Bishop
			board[0][2] = std::move(std::unique_ptr<Piece>(new Bishop(Color::Black, 0, 2, 2)));
			//Queen
			board[0][3] = std::move(std::unique_ptr<Piece>(new Queen(Color::Black, 0, 3, 3)));
			//King
			board[0][4] = std::move(std::unique_ptr<Piece>(new King(Color::Black, 0, 4, 4)));
			//Bishop 2
			board[0][5] = std::move(std::unique_ptr<Piece>(new Bishop(Color::Black, 0, 5, 5)));
			//Horse 2
			board[0][6] = std::move(std::unique_ptr<Piece>(new Horse(Color::Black, 0, 6, 6)));
			//Rook 2
			board[0][7] = std::move(std::unique_ptr<Piece>(new Rook(Color::Black, 0, 7, 7)));

			//Pawns
			for (int i = 0; i < 8; i++) {
				board[1][i] = std::move(std::unique_ptr<Piece>(new Pawn(Color::Black, 1, i, i + 8)));
			}

			//Black pieces

			//Rook
			board[7][0] = std::move(std::unique_ptr<Piece>(new Rook(Color::White, 7, 0, 16)));
			//Horse
			board[7][1] = std::move(std::unique_ptr<Piece>(new Horse(Color::White, 7, 1, 17)));
			//Bishop
			board[7][2] = std::move(std::unique_ptr<Piece>(new Bishop(Color::White, 7, 2, 18)));
			//Queen
			board[7][3] = std::move(std::unique_ptr<Piece>(new Queen(Color::White, 7, 3, 19)));
			//King
			board[7][4] = std::move(std::unique_ptr<Piece>(new King(Color::White, 7, 4, 20)));
			//Bishop 2
			board[7][5] = std::move(std::unique_ptr<Piece>(new Bishop(Color::White, 7, 5, 21)));
			//Horse 2
			board[7][6] = std::move(std::unique_ptr<Piece>(new Horse(Color::White, 7, 6, 22)));
			//Rook 2
			board[7][7] = std::move(std::unique_ptr<Piece>(new Rook(Color::White, 7, 7, 23)));

			for (int i = 0; i < 8; i++) {
				board[6][i] = std::move(std::unique_ptr<Piece>(new Pawn(Color::White, 6, i, i + 24)));
			}
		}

		bool move(int currentCol, int CurrentRow, int newCol, int newRow) {
			if (board[currentCol][CurrentRow] != nullptr) {
				Chess::MoveResponse result = board[currentCol][CurrentRow]->checkMove(newCol, newRow, *this);
				if (result == Chess::MoveResponse::Ate || result == Chess::MoveResponse::Moved) {
					this->board[newCol][newRow] = std::move(this->board[currentCol][CurrentRow]);
					board[currentCol][CurrentRow] = nullptr;
					board[newCol][newRow]->setCurrentCol(newCol);
					board[newCol][newRow]->setCurrentRow(newRow);
					return true;
				}
			}
			return false;
		}

		bool isEmpty(int row, int col) const {
			return board[row][col] == nullptr;
		}

		Color getColor(int col, int row) const {
			return board[col][row]->getColor();
		}
	};
}

#endif // !BOARD_H