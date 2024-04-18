#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include "Board.h"
#include "RandomDiviner.h"

void GetUserInput(int8_t& col, int8_t& row, const CellType currentPlayer) {
    std::cout << "Player " << (currentPlayer == CellType::eWhite ? "White" : "Black") << " move col, row:";
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
            std::cout << std::to_underlying(pBoard->GetCell(col, row));
        }
        std::cout << std::endl;
    }

    std::cout << "White: " << (int)pBoard->GetScore(CellType::eWhite) << std::endl;
    std::cout << "Black: " << (int)pBoard->GetScore(CellType::eBlack) << std::endl;

}

int main() {
    std::shared_ptr<IBoard> pBoard = std::make_shared<Board>();
    CellType currentPlayer = CellType::eBlack;
    RandomDiviner randomDiviner{};
    bool hasPreviousPlayerSkip{ false };
    while (true) {
        int8_t col{ -1 }, row{ -1 };
        currentPlayer = (currentPlayer == CellType::eWhite) ? CellType::eBlack : CellType::eWhite;
        Print(pBoard);
        auto moves = pBoard->GetAvailableMoves(currentPlayer);
        if (moves.empty()) {
            std::cout << "No available moves for player " << (currentPlayer==CellType::eWhite?"White":"Black") << std::endl;
            if (hasPreviousPlayerSkip) {
                break;
            }
            hasPreviousPlayerSkip = true;
            continue;
        }
        hasPreviousPlayerSkip = false;

        if (currentPlayer == CellType::eWhite) {
            GetUserInput(col, row, currentPlayer);
            while (not pBoard->IsValidMove(col, row, currentPlayer)) {
                std::cout << "col=" << (short)col << " row=" << (short)row << " invalid move!" << std::endl;
                GetUserInput(col, row, currentPlayer);
            }
        }
        else {
            randomDiviner.Choose(pBoard, currentPlayer, col, row);
            std::cout << "Player Black move col, row:" << (short)col << "," << (short)row << std::endl;
        }
        pBoard->MakeMove(col, row, currentPlayer);
    }


    
    return 0;
}
