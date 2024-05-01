#pragma once
#include <stdint.h>
#include <vector>
#include <utility>
#include <optional>

enum class Player:uint8_t
{
	eWhite='W',
	eBlack='B'
};

struct Move
{
	Player player{};
	uint8_t row{};
	uint8_t col{};
};

class IBoard
{
protected:
	virtual void togglePlayer() = 0;

public:
	virtual bool isValidMove(const uint8_t col, const uint8_t row) const =0;
	virtual void makeMove(const uint8_t col, const uint8_t row) = 0;
	virtual void score(uint8_t& white, uint8_t& black) const = 0;
	virtual std::vector<Move> availableMoves() const = 0;
	virtual std::optional<Player> cell(const uint8_t col, const uint8_t row) const = 0;
	virtual std::shared_ptr<IBoard> duplicate() const = 0;
	virtual Player currentPlayer() const = 0;
	virtual bool gameOver() const = 0;
	virtual bool mustSkip() const = 0;
	virtual void skip() = 0;
	virtual Move lastMove() const = 0;
};

