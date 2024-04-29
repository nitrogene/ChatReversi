#include "FailSoftAlphaBetaMinimaxDiviner.h"
#include "Node.h"

int64_t FailSoftAlphaBetaMinimaxDiviner::minimax(std::shared_ptr<IBoard> pNode, const size_t depth, int64_t& alpha, int64_t& beta, const bool maximizingPlayer)
{
	int64_t value{};

	if (depth == 0 || Node::terminal(pNode)) {
		return Node::value(pNode);
	}
	else if (maximizingPlayer) {
		value = -std::numeric_limits<decltype(value)>::max();
		for (auto& pChild : Node::children(pNode)) {
			auto localValue = minimax(pChild, depth - 1, alpha, beta, false);
			if (localValue > value) {
				value = localValue;
				if (m_depth == depth) {
					m_bestMove = pChild->lastMove();
				}
			}
			alpha = std::max(alpha, value);
			if (value >= beta) {
				break;
			}
		}
	}
	else {
		value = std::numeric_limits<decltype(value)>::max();
		for (auto& pChild : Node::children(pNode)) {
			Move localMove{ pChild->lastMove() };
			auto localValue = minimax(pChild, depth - 1, alpha, beta, true);
			if (localValue < value) {
				value = localValue;
			}
			beta = std::min(beta, value);
			if (value <= alpha) {
				break;
			}
		}
	}

	return value;
}

FailSoftAlphaBetaMinimaxDiviner::FailSoftAlphaBetaMinimaxDiviner(size_t depth) :m_depth(depth)
{
}

void FailSoftAlphaBetaMinimaxDiviner::choose(std::shared_ptr<IBoard> pBoard)
{
	int64_t alpha{ -std::numeric_limits<int64_t>::max() };
	int64_t beta{ -alpha };

	minimax(pBoard, m_depth, alpha, beta, true);
	pBoard->makeMove(m_bestMove.col, m_bestMove.row);
}
