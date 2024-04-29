#pragma once
#include "IDiviner.h"

class HumanDiviner : public IDiviner
{
private:
	void GetUserInput(int8_t& col, int8_t& row);

public:
	virtual void choose(std::shared_ptr<IBoard> pBoard) override;
};