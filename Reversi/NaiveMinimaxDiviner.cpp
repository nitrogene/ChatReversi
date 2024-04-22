#include "NaiveMinimaxDiviner.h"

Node::Node(std::shared_ptr<IBoard> pBoard)
{
	m_pBoard = pBoard;
	m_value = m_pBoard->score(m_pBoard->currentPlayer());
	m_isTerminal = m_pBoard->gameOver();
}

bool Node::terminal() const
{
	return m_isTerminal;
}

int64_t Node::value() const
{
	return m_value;
}

std::vector<Node> Node::children() const
{
	std::vector<Node> children{};

	if (not m_isTerminal) {

		if (m_pBoard->mustSkip()) {
			auto currentBoard = m_pBoard->duplicate();
			currentBoard->skip();
			children.emplace_back(m_pBoard);
		}
		else {
			const auto& moves = m_pBoard->availableMoves();
			for (const auto& move : moves) {
				auto currentBoard = m_pBoard->duplicate();
				currentBoard->makeMove(move.first, move.second);
				children.emplace_back(currentBoard);
			}
		}
	}

	return children;
}

int64_t NaiveMinimaxDiviner::minimax(const Node& node, const size_t depth, const bool maximizingPlayer, Node& bestMove) const
{
	int64_t value{};

	if (depth == 0 || node.terminal()) {
		return node.value();
	}
	else if (maximizingPlayer) {
		value = -std::numeric_limits<decltype(value)>::max();
		for (auto& child : node.children()) {
			value = std::max(value, minimax(child, depth - 1, false));
		}
	}
	else {
		value = std::numeric_limits<decltype(value)>::max();
		for (auto& child : node.children()) {
			value = std::min(value, minimax(child, depth - 1, true));
		}
	}

	return value;
}

void NaiveMinimaxDiviner::choose(const std::shared_ptr<IBoard>& pBoard) const
{
	Node origin{ pBoard };
	Move bestMove;
	minimax(origin, 4, true, bestMove);
}
