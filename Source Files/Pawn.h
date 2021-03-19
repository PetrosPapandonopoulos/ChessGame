#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include <vector>

namespace Chess {

    class Board;

    class Pawn : public Piece {

    public:
        Pawn(Color color, int currentCol, int currentRow, int numOfSprite) : Piece(color, currentCol, currentRow,
                                                                                   numOfSprite) {}

        MoveResponse checkMove(int newCol, int newRow, const Board &board) override;

    };
}

#endif // !PAWN_H 
