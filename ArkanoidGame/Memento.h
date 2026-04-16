#pragma once
#include "Block.h"
#include <vector>
#include <memory>

namespace ArkanoidGame
{
	class Memento
	{
	public:
		Memento(int score, int currentLevel, int breackableBlocksCount,
			const std::vector<std::shared_ptr<Block>>& blocks)
			: score(score)
			, currentLevel(currentLevel)
			, breackableBlocksCount(breackableBlocksCount)
			, blocks(blocks)
		{}

		int GetScore() const { return score; }
		int GetCurrentLevel() const { return currentLevel; }
		int GetBreackableBlocksCount() const { return breackableBlocksCount; }
		const std::vector<std::shared_ptr<Block>>& GetBlocks() const { return blocks; }

	private:
		int score;
		int currentLevel;
		int breackableBlocksCount;
		std::vector<std::shared_ptr<Block>> blocks;
	};
}