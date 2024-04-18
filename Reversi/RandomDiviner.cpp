#include "RandomDiviner.h"

void RandomDiviner::Choose(const std::unique_ptr<IBoard>& pBoard, const CellType currentPlayer, int8_t& col, int8_t& row)
{
	auto moves = pBoard->GetAvailableMoves(currentPlayer);
	std::uniform_int_distribution<unsigned short> m_range{ 0, (uint8_t)(moves.size()-1)};
	auto pos = moves[static_cast<size_t>(m_range(m_generator))];
	row = pos / 8;
	col = pos % 8;
}
