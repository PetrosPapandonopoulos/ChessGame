#ifndef PIECE_H
#define PIECE_H

#include <vector>

namespace Chess {

    class Board;

    enum class Color {
        White,
        Black,
        None
    };

    enum class MoveResponse {
        Moved,
        Failed,
        Ate
    };

    enum class Type {
        Rook,
        Horse,
        Bishop,
        Queen,
        King,
        Pawn
    };

    class Piece {

    protected:
        Color color;
        int currentCol;
        int currentRow;
        int numOfSprite;
        Type pieceName;

        Piece(Color color, int currentCol, int currentRow, int numOfSprite, Type pieceName);

        bool addIfValid(const Board &board, std::vector<std::pair<int, int>> &validCoordinates,
                        std::pair<int, int> coordinates);

        static MoveResponse
        checkIfBelongs(std::vector<std::pair<int, int>> validCoordinates, std::pair<int, int> inputCoordinates,
                       const Board &board);

    public:
        Color getColor();

        Type getPieceName();

        int getNumOfSprite() const;

        void setCurrentCol(int currentCol);

        void setCurrentRow(int currentRow);

        virtual MoveResponse checkMove(int newCol, int newRow, const Board &board) = 0;

        virtual void getAllPossibleMoves(std::vector<std::pair<int, int>> &validCoordinates, const Board &board) = 0;

    };
}

#endif //!PIECE_H
