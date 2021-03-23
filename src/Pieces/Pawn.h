#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include <vector>

namespace Chess {
    
    class Board;
    
    class Pawn : public Piece {
    
    public:
        Pawn(Color color, int currentCol, int currentRow, int numOfSprite, Type pieceName, bool hasMoved) : Piece(color,
                                                                                                                  currentCol,
                                                                                                                  currentRow,
                                                                                                                  numOfSprite,
                                                                                                                  pieceName,
                                                                                                                  hasMoved) {}
        
        MoveResponse checkMove(int newCol, int newRow, const Board &board) override;
        
        void getAllPossibleMoves(std::vector<std::pair<int, int>> &validCoordinates, const Board &board) override;
        
    };
}

#endif // !PAWN_H 
