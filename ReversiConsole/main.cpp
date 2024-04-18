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

int main() {
    std::unique_ptr<IBoard> pBoard = std::make_unique<Board>();
    CellType currentPlayer = CellType::eBlack;
    RandomDiviner randomDiviner{};
    bool hasPreviousPlayerSkip{ false };
    while (true) {
        int8_t col{ -1 }, row{ -1 };
        currentPlayer = (currentPlayer == CellType::eWhite) ? CellType::eBlack : CellType::eWhite;
        pBoard->Print();
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
