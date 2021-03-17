#ifndef PIECE_H
#define PIECE_H

#include <vector>

namespace Chess {

	class Board;

	enum class Color {
		White,
		Black
	};

	enum class MoveResponse {
		Moved,
		Failed,
		Ate
	};

	class Piece {

	protected:
		Color color;
		int currentCol;
		int currentRow;
		int numOfSprite;

		Piece(Color color, int currentCol, int currentRow, int numOfSprite);

		bool addIfValid(const Board& board, std::vector<std::pair<int, int>>& validCordinates, std::pair<int, int>cordinates);

		MoveResponse checkIfBelongs(std::vector<std::pair<int, int>> validCordinates, std::pair<int, int> inputCordinates, const Board& board);

	public:
		Color getColor() {
			return color;
		}

		int getCurrentCol() {
			return currentCol;
		}

		int getCurrentRow() {
			return currentRow;
		}

		int getNumOfSprite() {
			return numOfSprite;
		}

		void setCurrentCol(int currentCol) {
			this->currentCol = currentCol;
		}

		void setCurrentRow(int currentRow) {
			this->currentRow = currentRow;
		}

		virtual MoveResponse checkMove(int newCol, int newRow, const Board& board) = 0;

	};
}

#endif //!PIECE_H
