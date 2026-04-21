#pragma once
#include "Bonus.h"

namespace ArkanoidGame
{
	class PlatformBonusItem : public Bonus
	{
	public:
		PlatformBonusItem(const sf::Vector2f& position);
		~PlatformBonusItem() = default;

		void Activate() override;
		void Update(float timeDelta) override;

	};

	
}