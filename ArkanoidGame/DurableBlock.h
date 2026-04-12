#pragma once
#include "Block.h"

namespace ArkanoidGame
{
	class DurableBlock : public Block
	{
	public:
		DurableBlock(const sf::Vector2f& position);
		~DurableBlock() = default;


	private:
		void OnHit() override;
		void UpdateVisual();
	};
}