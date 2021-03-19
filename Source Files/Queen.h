#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

namespace Chess {

    class Board;

    class Queen : public Piece {
    private:
        void addSlidingMovesHorVer(std::vector<std::pair<int, int>> &validCoordinates, int start, int end, int dir,
                                   const Board &board, bool checkCol);

        void addSlidingMovesDiagonal(std::vector<std::pair<int, int>> &validCoordinates, std::pair<int, int> direction,
                                     const Board &board);

    public:
        Queen(Color color, int currentCol, int currentRow, int numOfSprite) : Piece(color, currentCol, currentRow,
                                                                                    numOfSprite) {}

        MoveResponse checkMove(int newCol, int newRow, const Board &board) override;
    };
}

#endif // !QUEEN_H

