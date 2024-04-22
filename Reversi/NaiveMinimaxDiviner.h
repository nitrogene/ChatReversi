#pragma once
#include <functional>
#include <vector>
#include "IDiviner.h"

// https://en.wikipedia.org/wiki/Minimax

class Node
{
private:
	bool m_isTerminal{ false };
	int64_t m_value{ 0 };
	std::shared_ptr<IBoard> m_pBoard{};

public:
	Node(std::shared_ptr<IBoard> pBoard);

	bool terminal() const;

	int64_t value() const;

	std::vector<Node> children() const;
};

class NaiveMinimaxDiviner : public IDiviner
{
private:
	int64_t minimax(const Node& node, const size_t depth, const bool maximizingPlayer, Node& bestMove) const;

public:
	virtual void choose(const std::shared_ptr<IBoard>& pBoard) const override;
};