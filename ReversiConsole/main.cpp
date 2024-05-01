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
            auto player = pBoard->cell(col, row);
            char cell{ ' ' };
            if (player.has_value()) {
                cell = std::to_underlying(pBoard->cell(col, row).value());
            }
            std::cout << cell;
        }
        std::cout << std::endl;
    }

    uint8_t whiteScore, blackScore;
    pBoard->score(whiteScore, blackScore);
    std::cout << "White: " << (int)whiteScore << std::endl;
    std::cout << "Black: " << (int)blackScore << std::endl;
}

int main() {
    std::shared_ptr<IBoard> pBoard = std::make_shared<Board>();
    RandomDiviner whitePlayer{};
    FailSoftAlphaBetaMinimaxDiviner blackPlayer{64};
    while (not pBoard->gameOver()) {
        auto currentPlayer = pBoard->currentPlayer();
        Print(pBoard);

        if (pBoard->mustSkip()) {
            std::cout << (currentPlayer==Player::eWhite?"White":"Black") << " player has skipped" << std::endl;
            pBoard->skip();
            continue;
        }
        
        if (pBoard->currentPlayer() == Player::eWhite) {
            whitePlayer.choose(pBoard);
        }
        else {
            blackPlayer.choose(pBoard);
        }
    }

    // Game over board
    Print(pBoard);

    uint8_t whiteScore, blackScore;
    pBoard->score(whiteScore, blackScore);
    if (whiteScore > blackScore) {
        std::cout << "White player has won" << std::endl;
    }
    else if (whiteScore < blackScore) {
        std::cout << "Black player has won" << std::endl;
    }
    else
    {
        std::cout << "draw" << std::endl;
    }
    
    return 0;
}
