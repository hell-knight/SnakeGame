#pragma once
#include <memory>
#include "Block.h"
#include "Collidable.h"

namespace ArkanoidGame
{
	class ThreeHitBlock : public SmoothDestroyableBlock
	{
	public:
		ThreeHitBlock(const sf::Vector2f& position);
		int GetPoints() const override { return 75; }

	private:
		void OnHit() override;
		void StageChange();
		void TakeDamage(int damage);
	};
}