#include <iostream>
#include <utility>
#include <bit>
#include "Board.h"

const int8_t Board::g_dirs[] = { -7, -8, -9, -1, 1, 7, 8, 9 };

void Board::togglePlayer()
{
	m_currentPlayer = (m_currentPlayer == Player::eWhite) ? Player::eBlack : Player::eWhite;
}

uint64_t Board::coordinatesToBitPos(const uint8_t col, const uint8_t row) const
{
	return ((uint64_t)1) << (((uint64_t)col) + (((uint64_t)row) << 3));
}

bool Board::canFlipInDir(const uint64_t bitPos, const int8_t dir) const
{
	// TODO:
	// checking overflow with
	// #include <stdckdint.h>
	// bool ckd_add(type1 * result, type2 a, type3 b);
	// bool ckd_sub(type1 * result, type2 a, type3 b);
	// bool ckd_mul(type1 * result, type2 a, type3 b);



	int8_t drow, dcol;
	convertDir(dir, drow, dcol);
	int8_t curPos = pos;
	int8_t nextRow = (curPos / 8) + drow;
	int8_t nextCol = (curPos % 8) + dcol;
	CellType opponentPlayer = (m_currentPlayer == CellType::eWhite) ? CellType::eBlack : CellType::eWhite;

	while (nextRow >= 0 && nextRow < 8 && nextCol >= 0 && nextCol < 8 && m_cells[curPos+dir]== opponentPlayer) {
		curPos += dir;
		nextRow = (curPos / 8) + drow;
		nextCol = (curPos % 8) + dcol;
	}

	return curPos != pos && nextRow >= 0 && nextRow < 8 && nextCol >= 0 && nextCol < 8 && m_cells[curPos + dir] == m_currentPlayer;
}

bool Board::isValidMove(const uint8_t col, const uint8_t row) const
{
	uint64_t bitPos{ coordinatesToBitPos(col, row) };

	// Cell must be empty
	if (m_whiteCells & bitPos || m_blackCells & bitPos) {
		return false;
	}

	// Can we at least flip a cell in at least one direction?
	for (const auto dir : g_dirs) {
		if (canFlipInDir(bitPos, dir)) {
			return true;
		}
	}

	return false;
}

void Board::makeMove(const uint8_t col, const uint8_t row)
{
	//if (not isValidMove(col, row)) {
	//	return;
	//}

	//int8_t pos = coordinatesToCellIndex(col, row);

	//for (const auto dir : g_dirs) {
	//	if (not canFlipInDir(pos, dir)) {
	//		continue;
	//	}
	//	flip(pos, dir);
	//}
	//m_cells[pos] = m_currentPlayer;

	//m_moves.emplace_back(m_currentPlayer, row, col);

	//togglePlayer();
}

//
//const int8_t Board::g_dirs[] = { -7, -8, -9, -1, 1, 7, 8, 9 };
//
//uint8_t Board::coordinatesToCellIndex(const int8_t col, const int8_t row) const
//{
//	if (col<0 || col >= 8 || row<0 || row >= 8) {
//		throw std::exception("Invalid coordinates");
//	}
//	return col + (row << 3);
//}

void Board::score(uint8_t& white, uint8_t& black) const
{
	white = std::popcount(m_whiteCells);
	black = std::popcount(m_blackCells);
}

std::vector<Move> Board::availableMoves() const
{
	std::vector<Move> moves{};

	for (uint8_t pos = 0; pos < 64; ++pos) {
		uint8_t row = pos / 8;
		uint8_t col = pos % 8;
		if (isValidMove(col, row)) {
			moves.push_back({ m_currentPlayer, row, col });
		}
	}

	return moves;
}

std::optional<Player> Board::cell(const uint8_t col, const uint8_t row) const
{
	uint64_t pos{ coordinatesToBitPos(col, row) };

	if (m_whiteCells & pos) {
		return Player::eWhite;
	}

	if (m_blackCells & pos) {
		return Player::eBlack;
	}
	
	return {};
}

std::shared_ptr<IBoard> Board::duplicate() const
{
	auto pBoard = std::make_shared<Board>();
	//pBoard->cells(m_cells);
	//pBoard->moves(m_moves);
	//pBoard->currentPlayer(m_currentPlayer);
	return pBoard;
}

Player Board::currentPlayer() const
{
	return m_currentPlayer;
}

bool Board::gameOver() const
{
	if (mustSkip())
	{
		auto tmp = std::dynamic_pointer_cast<Board>(duplicate());
		tmp->togglePlayer();
		if (tmp->mustSkip()) {
			return true;
		}
	}

	return false;
}

bool Board::mustSkip() const
{
	for (int8_t pos = 0; pos < 64; ++pos) {
		int8_t row = pos / 8;
		int8_t col = pos % 8;
		if (isValidMove(col, row)) {
			return false;
		}
	}

	return true;
}

void Board::skip()
{
	togglePlayer();
}

Move Board::lastMove() const
{
	return m_moves.back();
}

//void Board::flip(const int8_t pos, const int8_t dir)
//{
//	// ChatGPT powered
//	int nextPos = pos + dir;
//
//	while (m_cells[nextPos] != CellType::eEmpty && m_cells[nextPos] != m_currentPlayer) {
//		m_cells[nextPos] = m_currentPlayer;
//		nextPos += dir;
//	}
//}
//
//
//
//
//
//
//
//
//
//Cells Board::cells() const
//{
//	return m_cells;
//}
//
//void Board::cells(const Cells& cells)
//{
//	m_cells = cells;
//}
//
//
//
//constexpr void Board::convertDir(const int8_t dir, int8_t& drow, int8_t& dcol) const {
//	if (dir == -9) {
//		drow = -1;
//		dcol = -1;
//	}
//	else if (dir == -8) {
//		drow = -1;
//		dcol = 0;
//	}
//	else if (dir == -7) {
//		drow = -1;
//		dcol = 1;
//	}
//	else if (dir == -1) {
//		drow = 0;
//		dcol = -1;
//	}
//	else if (dir == 1) {
//		drow = 0;
//		dcol = 1;
//	}
//	else if (dir == 7) {
//		drow = 1;
//		dcol = -1;
//	}
//	else if (dir == 8) {
//		drow = 1;
//		dcol = 0;
//	}
//	else if (dir == 9) {
//		drow = 1;
//		dcol = 1;
//	}
//}

//
//
//
//
//
//
//
//
//
//

//
//void Board::moves(const std::vector<Move>& moves)
//{
//	m_moves = moves;
//}
//
