#pragma once
#include <memory>
#include <vector>
#include "IBoard.h"

namespace Node
{
	bool terminal(std::shared_ptr<IBoard> pBoard);

	int64_t value(std::shared_ptr<IBoard> pBoard);

	std::vector<std::shared_ptr<IBoard>> children(std::shared_ptr<IBoard> pBoard);
};