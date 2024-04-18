#pragma once
#include "IDiviner.h"

// https://en.wikipedia.org/wiki/Minimax

class NaiveMinimaxDiviner : public IDiviner
{
public:
	virtual void Choose(const std::unique_ptr<IBoard>& pBoard, const CellType currentPlayer, int8_t& col, int8_t& row) override;
};