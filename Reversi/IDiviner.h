#pragma once
#include<memory>
#include "IBoard.h"

class IDiviner
{
public:
	virtual void choose(std::shared_ptr<IBoard> pBoard) =0;
};