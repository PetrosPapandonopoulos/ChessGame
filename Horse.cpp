#include "Board.h"
#include "Horse.h"
#include <vector>


Chess::MoveResponse Chess::Horse::checkMove(int newCol, int newRow, const Board& board) {

	/* A vector used to store all the possible moves a pawn can make
	*based on its current cordinates*/

	std::vector<std::pair<int, int>> validCordinates;




	return MoveResponse::Ate;
}