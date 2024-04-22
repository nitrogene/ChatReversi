#pragma once
#include <stdint.h>
#include <vector>
#include <array>
#include <utility>

enum class CellType :uint8_t
{
	eEmpty = ' ',
	eBlack = 'B',
	eWhite = 'W'
};

struct Move
{
	CellType player{};
	int8_t row{};
	int8_t col{};
};

using Cells = std::array<CellType, 64>;

class IBoard
{
private:
	virtual void togglePlayer() = 0;

public:
	virtual bool isValidMove(const int8_t col, const int8_t row) const =0;
	virtual void makeMove(const int8_t col, const int8_t row) = 0;
	virtual uint8_t score(const CellType player) const = 0;
	virtual std::vector<std::pair<int8_t, int8_t>> availableMoves() const = 0;
	virtual CellType cell(const int8_t col, const int8_t row) const = 0;
	virtual Cells cells() const = 0;
	virtual void cells(const Cells& cells) = 0;
	virtual std::shared_ptr<IBoard> duplicate() const = 0;
	virtual CellType currentPlayer() const = 0;
	virtual bool gameOver() = 0;
	virtual bool mustSkip() = 0;
	virtual void skip() = 0;
	virtual Move lastMove() = 0;
};

