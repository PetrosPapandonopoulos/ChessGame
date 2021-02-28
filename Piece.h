#ifndef PIECE_H
#define PIECE_H

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

		Piece(Color color, int currentCol, int currentRow, int numOfSprite) :
			color(color), currentCol(currentCol), currentRow(currentRow), numOfSprite(numOfSprite) {
		}
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

#endif
