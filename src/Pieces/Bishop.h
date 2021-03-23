#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

namespace Chess {

    class Board;

    class Bishop : public Piece {
    protected:
        void addSlidingMoves(std::vector<std::pair<int, int>> &validCoordinates, std::pair<int, int> direction,
                             const Board &board);

    public:
        Bishop(Color color, int currentCol, int currentRow, int numOfSprite, Type pieceName, bool hasMoved) : Piece(color, currentCol, currentRow,
                                                                                     numOfSprite, pieceName, hasMoved) {}

        MoveResponse checkMove(int newCol, int newRow, const Board &board) override;

        void getAllPossibleMoves(std::vector<std::pair<int, int>>& validCoordinates, const Board &board) override;
    };

}

#endif // !BISHOP_H
