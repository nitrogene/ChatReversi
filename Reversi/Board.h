#pragma once
#include <array>
#include "IBoard.h"

class Board: public IBoard
{
private:
#define EMPTY CellType::eEmpty
#define BLACK CellType::eBlack
#define WHITE CellType::eWhite

	static const int8_t g_dirs[];

	std::array<CellType, 64> m_Cells{
		EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY, WHITE, BLACK, EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY, BLACK, WHITE, EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY
	};

#undef EMPTY
#undef BLACK
#undef WHITE

	uint8_t CoordinatesToCellIndex(const int8_t col, const int8_t row) const;
	bool CanFlipInDir(const int8_t pos, const int8_t dir, const CellType currentPlayer) const;
	void Flip(const int8_t pos, const int8_t dir, const CellType currentPlayer);
	constexpr void ConvertDir(const int8_t dir, int8_t& drow, int8_t& dcol) const;
public:
	virtual bool IsValidMove(const int8_t col, const int8_t row, const CellType currentPlayer) const override;
	virtual void MakeMove(const int8_t col, const int8_t row, const CellType currentPlayer) override;
	virtual uint8_t GetScore(const CellType currentPlayer) const override;
	virtual std::vector<std::pair<int8_t, int8_t>> GetAvailableMoves(const CellType currentPlayer) const override;
	virtual CellType GetCell(const int8_t col, const int8_t row) const override;
};

