#include <iostream>
#include <string>
#include <memory>
#include "Board.h"
#include "RandomDiviner.h"
#include "NaiveMinimaxDiviner.h"
#include "FailSoftAlphaBetaMinimaxDiviner.h"
#include "HumanDiviner.h"

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
    RandomDiviner whitePlayer{};
    FailSoftAlphaBetaMinimaxDiviner blackPlayer{64};
    while (not pBoard->gameOver()) {
        auto currentPlayer = pBoard->currentPlayer();
        Print(pBoard);

        if (pBoard->mustSkip()) {
            std::cout << (currentPlayer==CellType::eWhite?"White":"Black") << " player has skipped" << std::endl;
            pBoard->skip();
            continue;
        }
        
        if (pBoard->currentPlayer() == CellType::eWhite) {
            whitePlayer.choose(pBoard);
        }
        else {
            blackPlayer.choose(pBoard);
        }
    }

    // Game over board
    Print(pBoard);

    if (pBoard->score(CellType::eWhite) > pBoard->score(CellType::eBlack)) {
        std::cout << "White player has won" << std::endl;
    }
    else if (pBoard->score(CellType::eWhite) < pBoard->score(CellType::eBlack)) {
        std::cout << "Black player has won" << std::endl;
    }
    else
    {
        std::cout << "draw" << std::endl;
    }
    
    return 0;
}
