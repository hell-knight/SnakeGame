#include "GlassBlock.h"

namespace ArkanoidGame
{
	GlassBlock::GlassBlock(const sf::Vector2f& position)
		: Block(position, sf::Color(200, 240, 255, 60))
	{
	}

	bool GlassBlock::AffectsBallDirection() const
	{
		return false;
	}

	void GlassBlock::OnHit()
	{
		hitCount = 0;
	}
}