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
        Queen(Color color, int currentCol, int currentRow, int numOfSprite, Type pieceName, bool hasMoved) : Piece(
                color, currentCol, currentRow,
                numOfSprite, pieceName, hasMoved) {}
        
        MoveResponse checkMove(int newCol, int newRow, const Board &board) override;
        
        void getAllPossibleMoves(std::vector<std::pair<int, int>> &validCoordinates, const Board &board) override;
    };
}

#endif // !QUEEN_H

