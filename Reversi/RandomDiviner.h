#pragma once
#include <random>
#include "IDiviner.h"


class RandomDiviner : public IDiviner
{
private:
	std::random_device m_randomDevice;
	std::mt19937 m_generator{ m_randomDevice() };
public:
	virtual void choose(std::shared_ptr<IBoard> pBoard) override;
};