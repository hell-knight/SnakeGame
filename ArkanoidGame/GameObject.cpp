#include "GameObject.h"
#include "Sprite.h"

namespace ArkanoidGame
{
	void GameObject::Draw(sf::RenderWindow& window)
	{
		DrawSprite(sprite, window);
	}

	void GameObject::SetPosition(const sf::Vector2f& position)
	{
		sprite.setPosition(position);
	}
}