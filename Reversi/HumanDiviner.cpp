#include <sstream>
#include <iostream>

#include "HumanDiviner.h"

void HumanDiviner::GetUserInput(int8_t& col, int8_t& row) {
	std::cout << "Player White move col, row:";
	std::string line;
	std::getline(std::cin, line);
	sscanf_s(line.c_str(), "%hhd,%hhd", &col, &row);
}

void HumanDiviner::choose(std::shared_ptr<IBoard> pBoard)
{
	int8_t col{ -1 }, row{ -1 };
	GetUserInput(col, row);
	while (not pBoard->isValidMove(col, row)) {
		std::cout << "col=" << (short)col << " row=" << (short)row << " invalid move!" << std::endl;
		GetUserInput(col, row);
	}
	pBoard->makeMove(col, row);
}