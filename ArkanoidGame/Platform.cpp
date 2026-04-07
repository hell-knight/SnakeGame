#include "Platform.h"
#include "GameSettings.h"
#include <assert.h>
#include "Sprite.h"

namespace ArkanoidGame
{
	void Platform::Init()
	{
		assert(texture.loadFromFile(TEXTURES_PATH + "Platform.png"));
		
		InitSprite(sprite, PLATFORM_WIDTH, PLATFORM_HEIGHT, texture);
		sprite.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEGHT - PLATFORM_HEIGHT / 2.f);
		speed = PLATFORM_SPEED;
	}

	void Platform::Update(float timeDelta)
	{
		float moveX = 0.f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			moveX -= speed * timeDelta;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			moveX += speed * timeDelta;
		}

		sprite.move(moveX, 0.f);

		// Overshoot protection
		sf::FloatRect bounds = sprite.getGlobalBounds();
		float halfWidth = sprite.getGlobalBounds().width / 2.f;

		if (bounds.left < 0)
		{
			sprite.setPosition(halfWidth, sprite.getPosition().y);
		}
		if (bounds.left + bounds.width > SCREEN_WIDTH)
		{
			sprite.setPosition(SCREEN_WIDTH - halfWidth, sprite.getPosition().y);
		}
	}

	void Platform::Draw(sf::RenderWindow& window) const
	{
		window.draw(sprite);
	}

	sf::FloatRect Platform::GetBounds() const
	{
		return sprite.getGlobalBounds();
	}
}