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
        Horse(Color color, int currentCol, int currentRow, int numOfSprite, Type pieceName, bool hasMoved) : Piece(
                color, currentCol, currentRow,
                numOfSprite, pieceName, hasMoved) {}
        
        MoveResponse checkMove(int newCol, int newRow, const Board &board) override;
        
        void getAllPossibleMoves(std::vector<std::pair<int, int>> &validCoordinates, const Board &board) override;
    };
    
}

#endif // !HORSE_H
