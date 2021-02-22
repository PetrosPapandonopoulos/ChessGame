#ifndef PIECE_H
#define PIECE_H


namespace Chess{

	class Board;

	enum class Color {
		White,
		Black
	};

	class Piece {
	protected:
		Color color;
		int currentCol;
		int currentRow;
		Piece(Color color, int currentCol, int currentRow):
			color(color), currentCol(currentCol), currentRow(currentRow)
		{ }
		virtual bool checkMove() = 0;

	public:
		virtual bool move(int newCol, int newRow, Board board) = 0;
		Color getColor() {
			return color;
		}
	};
}

#endif
