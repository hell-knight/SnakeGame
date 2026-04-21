#include "ThreeHitBlock.h"
#include "GameSettings.h"
#include <iostream>
#include "BonusManager.h"
#include "FragileBlocksBonus.h"

namespace ArkanoidGame
{
	ThreeHitBlock::ThreeHitBlock(const sf::Vector2f& position)
		: SmoothDestroyableBlock(position, sf::Color::Magenta)
	{
		hitCount = 3;
	}

	void ThreeHitBlock::OnHit()
	{
		int damage = BLOCK_DAMAGE_CONTEXT.GetDamage(hitCount, hitCount);
		TakeDamage(damage);
		StageChange();
	}

	void ThreeHitBlock::TakeDamage(int damage)
	{
		std::cout << "ThreeHitBlock::TakeDamage(" << damage << ") HP before: " << hitCount << std::endl;

		hitCount -= damage;
		std::cout << "HP after: " << hitCount << std::endl;
		if (hitCount <= 0)
		{
			hitCount = 1;
			std::cout << "*** ThreeHitBlock:: BLOCK DESTROYED! Starting timer and spawning bonus ***" << std::endl;
			StartTimer(SETTINGS.BREAK_DELAY);
			BONUS_MANAGER.TrySpawnBonus(GetPosition());
			Emit();
		}
	}

	void ThreeHitBlock::StageChange()
	{
		if (hitCount == 2)
		{
			sprite.setColor(sf::Color::Red);
		}
		if (hitCount < 2)
		{
			sprite.setColor(sf::Color::Green);
			color = sf::Color::Green;
		}
	}


}