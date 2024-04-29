#pragma once
#include <functional>
#include <vector>
#include "IDiviner.h"

// https://en.wikipedia.org/wiki/Minimax
class NaiveMinimaxDiviner : public IDiviner
{
private:
	Move m_bestMove{};
	size_t m_depth{};

	int64_t minimax(std::shared_ptr<IBoard> pNode, const size_t depth, const bool maximizingPlayer);

public:
	NaiveMinimaxDiviner(size_t depth);

	virtual void choose(std::shared_ptr<IBoard> pBoard) override;
};