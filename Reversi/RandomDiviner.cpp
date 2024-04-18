#include "RandomDiviner.h"

void RandomDiviner::Choose(const std::shared_ptr<IBoard>& pBoard, const CellType currentPlayer, int8_t& col, int8_t& row)
{
	auto moves = pBoard->GetAvailableMoves(currentPlayer);
	std::uniform_int_distribution<unsigned short> m_range{ 0, (uint8_t)(moves.size()-1)};
	auto move = moves[static_cast<size_t>(m_range(m_generator))];
	row = move.first;
	col = move.second;
}
