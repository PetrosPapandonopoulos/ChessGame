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
		Piece(Color color, int currentCol, int currentRow) :
			color(color), currentCol(currentCol), currentRow(currentRow) {
		}

	public:
		virtual MoveResponse checkMove(int newCol, int newRow, const Board& board) = 0;

		Color getColor() {
			return color;
		}
	};
}

#endif
