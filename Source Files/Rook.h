#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

namespace Chess {

    class Board;

    class Rook : public Piece {
    protected:
        void addSlidingMoves(std::vector<std::pair<int, int>> &validCoordinates, int start, int end, int dir,
                             const Board &board, bool checkRow);

    public:
        Rook(Color color, int currentCol, int currentRow, int numOfSprite, Type pieceName) : Piece(color, currentCol,
                                                                                                   currentRow,
                                                                                                   numOfSprite,
                                                                                                   pieceName) {}

        MoveResponse checkMove(int newCol, int newRow, const Board &board) override;

        void getAllPossibleMoves(std::vector<std::pair<int, int>> &validCoordinates, const Board &board) override;
    };
}

#endif //!ROOK_H
