#include "Node.h"

namespace Node
{
	bool terminal(std::shared_ptr<IBoard> pBoard)
	{
		return pBoard->gameOver();
	}

	int64_t value(std::shared_ptr<IBoard> pBoard)
	{
		uint8_t whiteScore, blackScore;
		pBoard->score(whiteScore, blackScore);

		return pBoard->currentPlayer() == Player::eWhite ? whiteScore : blackScore;
	}

	std::vector<std::shared_ptr<IBoard>> children(std::shared_ptr<IBoard> pBoard)
	{
		std::vector<std::shared_ptr<IBoard>> children{};

		if (not terminal(pBoard)) {

			if (pBoard->mustSkip()) {
				auto pCurrentBoard = pBoard->duplicate();
				pCurrentBoard->skip();
				children.emplace_back(pCurrentBoard);
			}
			else {
				const auto& moves = pBoard->availableMoves();
				for (const auto& move : moves) {
					auto pCurrentBoard = pBoard->duplicate();
					pCurrentBoard->makeMove(move.col, move.row);
					children.emplace_back(pCurrentBoard);
				}
			}
		}

		return children;
	}
}