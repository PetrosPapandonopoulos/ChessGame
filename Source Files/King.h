#ifndef KING_H
#define KING_H

#include "Piece.h"

namespace Chess {

    class Board;

    class King : public Piece {
    public:
        King(Color color, int currentCol, int currentRow, int numOfSprite, Type pieceName) : Piece(color, currentCol,
                                                                                                   currentRow,
                                                                                                   numOfSprite,
                                                                                                   pieceName) {}

        MoveResponse checkMove(int newCol, int newRow, const Board &board) override;

        void getAllPossibleMoves(std::vector<std::pair<int, int>> &validCoordinates, const Board &board) override;
    };

}

#endif // !KING_H
