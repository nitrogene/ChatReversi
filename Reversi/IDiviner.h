#pragma once
#include<memory>
#include "IBoard.h"

class IDiviner
{
public:
	virtual void Choose(const std::shared_ptr<IBoard>& pBoard, const CellType currentPlayer, int8_t& col, int8_t& row) =0;
};