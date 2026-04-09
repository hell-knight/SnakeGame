#include "Block.h"
#include "Sprite.h"
#include <assert.h>
#include "Ball.h"

namespace
{
	std::string TEXTURE_ID = "Platform";
}

namespace ArkanoidGame
{
	void Block::Init()
	{
		assert(texture.loadFromFile(TEXTURES_PATH + TEXTURE_ID + ".png"));
		InitSprite(sprite, BLOCK_WIDTH, BLOCK_HEIGHT, texture);
		sprite.setColor(sf::Color::Green);

	}
	bool Block::CheckCollisionWithBall(const Ball& ball) const
	{
		const auto rect = GetRect();
		const auto ballRect = ball.GetRect();
		return rect.intersects(ballRect);
	}
}