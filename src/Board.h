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
        std::pair<int, int> en_passantCord;
        
        void unMove(int currentCol, int CurrentRow, int newCol, int newRow, std::unique_ptr<Piece> &pieceEaten);
        
        void unMove(int currentCol, int CurrentRow, int newCol, int newRow);
    
        void moveObject(int currentCol, int currentRow, int newCol, int newRow);
    
    public:
        
        Board();
    
        MoveResponse move(int currentCol, int currentRow, int newCol, int newRow, bool pseudoMove);
        
        bool isEmpty(int row, int col) const;
        
        Color getColor(int col, int row) const;
        
        int getNumOfSprite(int i, int j) const;
        
        Color getWhoseTurn() const;
        
        bool getHasMoved(int col , int row) const;
        
        Type getPieceName(int col, int row) const;
        
        void nextTurn();
        
        Color checkForPromotion();
        
        bool promote(std::pair<int, int> pieceCoordinates, Type promoteTo);
        
        bool checkingForChecks(Color teamColor, std::pair<int, int> &kingCoordinates) const;
    
        bool checkForCheckmate(Color teamColor);
        
        void getAllPossibleMoves(std::pair<int, int> index, std::vector<std::pair<int, int>> &validCoordinates);
    };
}

#endif // !BOARD_H