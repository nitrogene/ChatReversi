#include <iostream>
#include <utility>

#include "Board.h"


const int8_t Board::g_dirs[] = { -7, -8, -9, -1, 1, 7, 8, 9 };

uint8_t Board::CoordinatesToCellIndex(const int8_t col, const int8_t row) const
{
	if (col<0 || col >= 8 || row<0 || row >= 8) {
		throw std::exception("Invalid coordinates");
	}
	return col + (row << 3);
}

bool Board::IsValidMove(const int8_t col, const int8_t row, const CellType cell) const
{
	try
	{
		int8_t pos = CoordinatesToCellIndex(col, row);
		// Cell must be empty
		if (m_Cells[pos] != CellType::eEmpty) {
			return false;
		}
		// Can we at least flip a cell in at least one direction?
		for (const auto dir : g_dirs) {
			if (CanFlipInDir(pos, dir, cell)) {
				return true;
			}
		}
	}
	catch (...)
	{
	}
	return false;
}

bool Board::CanFlipInDir(const int8_t pos, const int8_t dir, const CellType currentPlayer) const
{
	int8_t drow, dcol;
	ConvertDir(dir, drow, dcol);
	int8_t curPos = pos;
	int8_t nextRow = (curPos / 8) + drow;
	int8_t nextCol = (curPos % 8) + dcol;
	CellType opponentPlayer = (currentPlayer == CellType::eWhite) ? CellType::eBlack : CellType::eWhite;

	while (nextRow >= 0 && nextRow < 8 && nextCol >= 0 && nextCol < 8 && m_Cells[curPos+dir]== opponentPlayer) {
		curPos += dir;
		nextRow = (curPos / 8) + drow;
		nextCol = (curPos % 8) + dcol;
	}

	return curPos != pos && nextRow >= 0 && nextRow < 8 && nextCol >= 0 && nextCol < 8 && m_Cells[curPos + dir] == currentPlayer;
}
void Board::Flip(const int8_t pos, const int8_t dir, const CellType currentPlayer)
{
	// ChatGPT powered
	int nextPos = pos + dir;

	while (m_Cells[nextPos] != CellType::eEmpty && m_Cells[nextPos] != currentPlayer) {
		m_Cells[nextPos] = currentPlayer;
		nextPos += dir;
	}
}

void Board::MakeMove(const int8_t col, const int8_t row, const CellType currentPlayer)
{
	if (not IsValidMove(col, row, currentPlayer)) {
		return;
	}

	int8_t pos = CoordinatesToCellIndex(col, row);

	for (const auto dir : g_dirs) {
		if (not CanFlipInDir(pos, dir, currentPlayer)) {
			continue;
		}
		Flip(pos, dir, currentPlayer);
	}
	m_Cells[pos] = currentPlayer;
}

uint8_t Board::GetScore(const CellType currentPlayer) const
{
	uint8_t score{ 0 };

	for (auto c : m_Cells) {
		if (c == currentPlayer) {
			score++;
		}
	}

	return score;
}

std::vector<std::pair<int8_t, int8_t>> Board::GetAvailableMoves(const CellType currentPlayer) const
{
	std::vector<std::pair<int8_t, int8_t>> moves{};

	for (int8_t pos = 0; pos < 64; ++pos) {
		int8_t row = pos / 8;
		int8_t col = pos % 8;
		if (IsValidMove(col, row, currentPlayer)) {
			moves.push_back({ row, col });
		}
	}

	return moves;
}

CellType Board::GetCell(const int8_t col, const int8_t row) const
{
	return m_Cells[CoordinatesToCellIndex(col, row)];
}

constexpr void Board::ConvertDir(const int8_t dir, int8_t& drow, int8_t& dcol) const {
	if (dir == -9) {
		drow = -1;
		dcol = -1;
	}
	else if (dir == -8) {
		drow = -1;
		dcol = 0;
	}
	else if (dir == -7) {
		drow = -1;
		dcol = 1;
	}
	else if (dir == -1) {
		drow = 0;
		dcol = -1;
	}
	else if (dir == 1) {
		drow = 0;
		dcol = 1;
	}
	else if (dir == 7) {
		drow = 1;
		dcol = -1;
	}
	else if (dir == 8) {
		drow = 1;
		dcol = 0;
	}
	else if (dir == 9) {
		drow = 1;
		dcol = 1;
	}
}