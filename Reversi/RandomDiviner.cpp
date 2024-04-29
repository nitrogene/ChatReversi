#include "RandomDiviner.h"

void RandomDiviner::choose(std::shared_ptr<IBoard> pBoard)
{
	auto moves = pBoard->availableMoves();
	std::uniform_int_distribution<int> m_range{ (int)0, (int)(moves.size()-1)};
	auto i = m_range(m_generator);
	auto move = moves[i];
	pBoard->makeMove(move.col, move.row);
}
