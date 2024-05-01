#pragma once
#include "IBoard.h"

class Board: public IBoard
{
private:
	static const int8_t g_dirs[];
	uint64_t m_whiteCells{ 0b0000000000000000000000000001000000001000000000000000000000000000 };
	uint64_t m_blackCells{ 0b0000000000000000000000000000100000010000000000000000000000000000 };
	std::vector<Move> m_moves{};
	Player m_currentPlayer{Player::eWhite};

	virtual void togglePlayer() override;
	uint64_t coordinatesToBitPos(const uint8_t col, const uint8_t row) const;
	bool canFlipInDir(const uint64_t bitPos, const int8_t dir) const;


	//void flip(const int8_t pos, const int8_t dir);
	//constexpr void convertDir(const int8_t dir, int8_t& drow, int8_t& dcol) const;
	

	//void moves(const std::vector<Move>& moves);
	//void currentPlayer(CellType currentPlayer);

public:
	virtual bool isValidMove(const uint8_t col, const uint8_t row) const override;
	virtual void makeMove(const uint8_t col, const uint8_t row) override;
	virtual void score(uint8_t& white, uint8_t& black) const override;
	virtual std::vector<Move> availableMoves() const override;
	virtual std::optional<Player> cell(const uint8_t col, const uint8_t row) const override;
	virtual std::shared_ptr<IBoard> duplicate() const override;
	virtual Player currentPlayer() const override;
	virtual bool gameOver() const override;
	virtual bool mustSkip() const override;
	virtual void skip() override;
	virtual Move lastMove() const override;
};

