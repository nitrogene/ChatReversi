#include "NaiveMinimaxDiviner.h"
#include "Node.h"

int64_t NaiveMinimaxDiviner::minimax(std::shared_ptr<IBoard> pNode, const size_t depth, const bool maximizingPlayer)
{
	int64_t value{};

	if (depth == 0 || Node::terminal(pNode)) {
		return Node::value(pNode);
	}
	else if (maximizingPlayer) {
		value = -std::numeric_limits<decltype(value)>::max();
		for (auto& pChild : Node::children(pNode)) {
			auto localValue = minimax(pChild, depth - 1, false);
			if (localValue > value) {
				value = localValue;
				if (m_depth == depth) {
					m_bestMove = pChild->lastMove();
				}
			}
		}
	}
	else {
		value = std::numeric_limits<decltype(value)>::max();
		for (auto& pChild : Node::children(pNode)) {
			Move localMove{ pChild->lastMove() };
			auto localValue = minimax(pChild, depth - 1, true);
			if (localValue < value) {
				value = localValue;
			}
		}
	}

	return value;
}

NaiveMinimaxDiviner::NaiveMinimaxDiviner(size_t depth):m_depth(depth)
{
}

void NaiveMinimaxDiviner::choose(std::shared_ptr<IBoard> pBoard)
{
	minimax(pBoard, m_depth, true);
	pBoard->makeMove(m_bestMove.col, m_bestMove.row);
}
