#ifndef KING_H
#define KING_H

#include "Piece.h"

namespace Chess {

    class Board;

    class King : public Piece {
    public:
        King(Color color, int currentCol, int currentRow, int numOfSprite) : Piece(color, currentCol, currentRow,
                                                                                   numOfSprite) {}

        MoveResponse checkMove(int newCol, int newRow, const Board &board) override;
    };

}

#endif // !KING_H
