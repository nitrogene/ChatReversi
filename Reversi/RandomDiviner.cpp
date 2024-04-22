#include "RandomDiviner.h"

void RandomDiviner::choose(const std::shared_ptr<IBoard>& pBoard) const
{
	auto moves = pBoard->availableMoves();
	std::uniform_int_distribution<unsigned short> m_range{ 0, (uint8_t)(moves.size()-1)};
	auto move = moves[static_cast<size_t>(m_range(m_generator))];
	pBoard->makeMove(move.first, move.second);
}
