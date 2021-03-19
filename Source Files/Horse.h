#ifndef HORSE_H
#define HORSE_H

#include "Piece.h"

namespace Chess {

    class Board;

    class Horse : public Piece {
    private:
        void addHopMoves(std::vector<std::pair<int, int>> &validCoordinates, int Direction, const Board &board,
                         bool checkCol);

    public:
        Horse(Color color, int currentCol, int currentRow, int numOfSprite) : Piece(color, currentCol, currentRow,
                                                                                    numOfSprite) {}

        MoveResponse checkMove(int newCol, int newRow, const Board &board) override;
    };

}

#endif // !HORSE_H
