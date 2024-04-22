#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include "Board.h"
#include "RandomDiviner.h"
#include "NaiveMinimaxDiviner.h"

void GetUserInput(int8_t& col, int8_t& row) {
    std::cout << "Player White move col, row:";
    std::string line;
    std::getline(std::cin, line);
    sscanf_s(line.c_str(), "%hhd,%hhd", &col, &row);
}

void Print(std::shared_ptr<IBoard> pBoard)
{
    std::cout << ' ';
    for (uint8_t col = 0; col < 8; ++col) {
        std::cout << (size_t)col;
    }
    std::cout << std::endl;
    for (uint8_t row = 0; row < 8; ++row) {
        std::cout << (size_t)row;
        for (uint8_t col = 0; col < 8; ++col) {
            std::cout << std::to_underlying(pBoard->cell(col, row));
        }
        std::cout << std::endl;
    }

    std::cout << "White: " << (int)pBoard->score(CellType::eWhite) << std::endl;
    std::cout << "Black: " << (int)pBoard->score(CellType::eBlack) << std::endl;
}

int main() {
    std::shared_ptr<IBoard> pBoard = std::make_shared<Board>();
    NaiveMinimaxDiviner diviner{4};
    while (not pBoard->gameOver()) {
        int8_t col{ -1 }, row{ -1 };
        Print(pBoard);

        // Current player must skip?
        if (pBoard->mustSkip()) {
            std::cout << "skipping" << std::endl;
            pBoard->skip();
            continue;
        }

        if (pBoard->currentPlayer() == CellType::eWhite) {
            GetUserInput(col, row);
            while (not pBoard->isValidMove(col, row)) {
                std::cout << "col=" << (short)col << " row=" << (short)row << " invalid move!" << std::endl;
                GetUserInput(col, row);
            }
            pBoard->makeMove(col, row);
        }
        else {
            diviner.choose(pBoard);
            auto move = pBoard->lastMove();
            std::cout << "Player Black move col, row:" << (short)move.col << "," << (short)move.row << std::endl;
        }
        
    }
    Print(pBoard);
    
    return 0;
}
