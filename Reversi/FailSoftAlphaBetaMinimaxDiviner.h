#pragma once
#include <functional>
#include <vector>
#include "IDiviner.h"

// https://en.wikipedia.org/wiki/Minimax

namespace Node
{
	bool terminal(std::shared_ptr<IBoard> pBoard);

	int64_t value(std::shared_ptr<IBoard> pBoard);

	std::vector<std::shared_ptr<IBoard>> children(std::shared_ptr<IBoard> pBoard);
};

class FailSoftAlphaBetaMinimaxDiviner : public IDiviner
{
private:
	Move m_bestMove{};
	size_t m_depth{};

	int64_t minimax(std::shared_ptr<IBoard> pNode, const size_t depth, int64_t& alpha, int64_t& beta, const bool maximizingPlayer);

public:
	FailSoftAlphaBetaMinimaxDiviner(size_t depth);

	virtual void choose(std::shared_ptr<IBoard> pBoard) override;
};