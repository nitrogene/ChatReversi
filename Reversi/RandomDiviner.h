#pragma once
#include <random>
#include "IDiviner.h"


class RandomDiviner : public IDiviner
{
private:
	std::random_device m_randomDevice;
	std::mt19937 m_generator{ m_randomDevice() };
public:
	virtual void Choose(const std::shared_ptr<IBoard>& pBoard, const CellType currentPlayer, int8_t& col, int8_t& row) override;
};