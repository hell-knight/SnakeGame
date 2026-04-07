#include "Ball.h"
#include "Platform.h"
#include "GameSettings.h"
#include <assert.h>
#include "Sprite.h"

namespace ArkanoidGame
{
	void Ball::Init()
	{
		assert(texture.loadFromFile(TEXTURES_PATH + "Ball.png"));

		InitSprite(sprite, BALL_SIZE, BALL_SIZE, texture);
		sprite.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEGHT - PLATFORM_HEIGHT - BALL_SIZE / 2.f);
		velocity = {250.f, -250.f};
	}

	void Ball::Update(float timeDelta, const Platform& platform)
	{
		sprite.move(velocity * timeDelta);

		sf::FloatRect bounds = sprite.getGlobalBounds();

		if (bounds.left <= 0 || bounds.left + bounds.width >= SCREEN_WIDTH)
		{
			BounceX();
		}

		if (bounds.top <= 0)
		{
			BounceY();
		}

		// Jump off the platform
		if (bounds.intersects(platform.GetBounds()) && velocity.y > 0)
		{
			BounceY();
		}

		// Fell down — reset
		if (bounds.top + bounds.height >= SCREEN_HEGHT)
		{
			Init();
		}
	}

	void Ball::Draw(sf::RenderWindow& window) const
	{
		window.draw(sprite);
	}

	sf::FloatRect Ball::GetBounds() const
	{
		return sprite.getGlobalBounds();
	}

	void Ball::BounceX()
	{
		velocity.x = -velocity.x;
	}

	void Ball::BounceY()
	{
		velocity.y = -velocity.y;
	}
}