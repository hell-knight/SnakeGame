#include "Ball.h"
#include "Platform.h"
#include "GameSettings.h"
#include <assert.h>
#include "Sprite.h"
#include "Block.h"

namespace
{
	// id textures

	const std::string TEXTURE_ID = "Ball";
}

namespace ArkanoidGame
{
	void Ball::Init()
	{
		assert(texture.loadFromFile(TEXTURES_PATH + TEXTURE_ID + ".png"));

		InitSprite(sprite, BALL_SIZE, BALL_SIZE, texture);
		sprite.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - PLATFORM_HEIGHT - BALL_SIZE / 2.f);
		
		const float angle = 45.f + rand() % 90;	// [45, 135] degree
		const auto pi = std::acos(-1.f);
		direction.x = std::cos(pi / 180.f * angle);
		direction.y = std::sin(pi / 180.f * angle);
	}

	void Ball::Update(float timeDelta)
	{
		const auto pos = sprite.getPosition() + BALL_SPEED * timeDelta * direction;
		sprite.setPosition(pos);

		if (pos.x - BALL_SIZE / 2.f <= 0 || pos.x + BALL_SIZE / 2.f >= SCREEN_WIDTH)
		{
			direction.x *= -1;
		}

		if(pos.y - BALL_SIZE / 2.f <= 0 || pos.y + BALL_SIZE / 2.f >= SCREEN_HEIGHT)
		{
			direction.y *= -1;
		}
	}

	void Ball::ReboundFromPlatform()
	{
		direction.y *= -1;
	}

	void Ball::ReboundFromBlock(const Block& block)
	{
		const auto ballPos = sprite.getPosition();
		const auto blockPos = block.GetPosition();
		const float dX = std::fabs(ballPos.x - blockPos.x);
		const float dY = std::fabs(ballPos.y - blockPos.y);

		if (dX > dY)
		{
			direction.x *= -1.f;
		}
		else
		{
			direction.y *= -1.f;
		}
	}

}