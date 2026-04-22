#include "Bonus.h"
#include "Platform.h"
#include "BonusManager.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <iostream>

namespace ArkanoidGame
{
	Bonus::Bonus(const sf::Vector2f& position)
		: GameObject(SETTINGS.TEXTURES_PATH + "ball.png", position, 25.f, 25.f)
	{
		SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
	}

	void Bonus::Update(float timeDelta)
	{
		auto pos = sprite.getPosition();
		pos.y += fallSpeed * timeDelta;
		sprite.setPosition(pos);

		// Check if bonus fell off screen
		if (pos.y > SETTINGS.SCREEN_HEIGHT + 50.f)
		{
			destroyed = true;
			std::cout << "Bonus fell off screen" << std::endl;
		}
	}

	void Bonus::Draw(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}

	bool Bonus::GetCollision(std::shared_ptr<Collidable> collidableObject) const
	{
		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
		if (!gameObject) return false;

		return GetRect().intersects(gameObject->GetRect());
	}

	void Bonus::OnHit()
	{
	}

}