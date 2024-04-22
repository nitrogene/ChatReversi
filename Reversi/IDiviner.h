#pragma once
#include<memory>
#include "IBoard.h"

class IDiviner
{
public:
	virtual void choose(const std::shared_ptr<IBoard>& pBoard) const =0;
};