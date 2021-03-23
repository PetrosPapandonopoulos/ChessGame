#ifndef BOARD_H
#define BOARD_H
#define BOARD_SIZE    8

#include "Pieces/Piece.h"
#include <memory>

namespace Chess {
    
    class Board {
    private:
        
        std::unique_ptr<Piece> board[BOARD_SIZE][BOARD_SIZE];
        Color turnFor;
        
        void unMove(int currentCol, int CurrentRow, int newCol, int newRow, std::unique_ptr<Piece> &pieceEaten);
        
        void unMove(int currentCol, int CurrentRow, int newCol, int newRow);
    
    public:
        
        Board();
        
        bool move(int currentCol, int currentRow, int newCol, int newRow, bool pseudoMove);
        
        bool isEmpty(int row, int col) const;
        
        Color getColor(int col, int row) const;
        
        int getNumOfSprite(int i, int j) const;
        
        Color getWhoseTurn() const;
        
        bool getHasMoved(int col , int row) const;
        
        void nextTurn();
        
        Color checkForPromotion();
        
        bool promote(std::pair<int, int> pieceCoordinates, Type promoteTo);
        
        bool checkingForChecks(Color teamColor, std::pair<int, int> &kingCoordinates) const;
    
        bool checkForCheckmate(Color teamColor);
    };
}

#endif // !BOARD_H