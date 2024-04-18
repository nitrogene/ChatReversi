#pragma once
#include <stdint.h>
#include <vector>

enum class CellType :uint8_t
{
	eEmpty = ' ',
	eBlack = 'B',
	eWhite = 'W'
};

class IBoard
{
public:
	virtual bool IsValidMove(const int8_t col, const int8_t row, const CellType currentPlayer) const =0;
	virtual void Print() const =0;
	virtual void MakeMove(const int8_t col, const int8_t row, const CellType currentPlayer) = 0;
	virtual uint8_t GetScore(const CellType currentPlayer) const = 0;
	virtual std::vector<int8_t> GetAvailableMoves(const CellType currentPlayer) const = 0;
};

