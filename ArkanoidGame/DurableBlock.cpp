#include "DurableBlock.h"

namespace ArkanoidGame
{
	DurableBlock::DurableBlock(const sf::Vector2f& position)
		: Block(position, sf::Color::Blue)
	{
		hitCount = 3;
	}

	void DurableBlock::OnHit()
	{
		if (hitCount > 0)
		{
			--hitCount;
			UpdateVisual();
		}
	}

	void DurableBlock::UpdateVisual()
	{
		if (hitCount == 2)
		{
			sprite.setColor(sf::Color::Red);
		}
		else if (hitCount == 1)
		{
			sprite.setColor(sf::Color::Green);
		}
	}

}