#pragma once
#pragma once
#include "Block.h"

namespace ArkanoidGame
{
	class GlassBlock : public Block
	{
	public:
		GlassBlock(const sf::Vector2f& position);
		~GlassBlock() = default;
		bool AffectsBallDirection() const override;
		
	private:
		void OnHit() override;
	};
}