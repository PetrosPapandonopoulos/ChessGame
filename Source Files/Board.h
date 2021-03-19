#ifndef BOARD_H
#define BOARD_H
#define BOARD_SIZE    8

#include "Piece.h"
#include <memory>

namespace Chess {

    class Board {
    private:

        std::unique_ptr<Piece> board[BOARD_SIZE][BOARD_SIZE];
        Color turnFor;

        void unMove(int currentCol, int CurrentRow, int newCol, int newRow, std::unique_ptr<Piece> &pieceEaten);
        void unMove(int currentCol, int CurrentRow, int newCol, int newRow);

    public:

        Board();

        bool move(int currentCol, int CurrentRow, int newCol, int newRow);

        bool isEmpty(int row, int col) const;

        Color getColor(int col, int row) const;

        int getNumOfSprite(int i, int j) const;

        Color getWhoseTurn() const;

        void nextTurn();
    };
}

#endif // !BOARD_H