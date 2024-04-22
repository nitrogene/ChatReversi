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
	Cells m_Cells{
		EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY, WHITE, BLACK, EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY, BLACK, WHITE, EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY
	};
	CellType m_currentPlayer{ WHITE };
	std::vector<Move> m_moves{};

#undef EMPTY
#undef BLACK
#undef WHITE

	uint8_t coordinatesToCellIndex(const int8_t col, const int8_t row) const;
	bool canFlipInDir(const int8_t pos, const int8_t dir) const;
	void flip(const int8_t pos, const int8_t dir);
	constexpr void convertDir(const int8_t dir, int8_t& drow, int8_t& dcol) const;
	virtual void togglePlayer() override;

public:
	virtual bool isValidMove(const int8_t col, const int8_t row) const override;
	virtual void makeMove(const int8_t col, const int8_t row) override;
	virtual uint8_t score(const CellType player) const override;
	virtual std::vector<std::pair<int8_t, int8_t>> availableMoves() const override;
	virtual CellType cell(const int8_t col, const int8_t row) const override;
	virtual Cells cells() const override;
	virtual void cells(const Cells& cells) override;
	virtual std::shared_ptr<IBoard> duplicate() const override;
	virtual CellType currentPlayer() const override;
	virtual bool gameOver() override;
	virtual bool mustSkip() override;
	virtual void skip() override;
	virtual Move lastMove() override;
};

