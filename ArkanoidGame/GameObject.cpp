#include "GameObject.h"
#include "Sprite.h"
#include <assert.h>
#include <iostream>

namespace ArkanoidGame
{
	GameObject::GameObject(const std::string& texturePath, const sf::Vector2f& position, float width, float height)
		: startPosition(position)
	{
		std::cout << "GameObject constructor: " << texturePath << std::endl;
		assert(texture.loadFromFile(texturePath));

		std::cout << "Texture loaded successfully: " << texturePath << std::endl;
		InitSprite(sprite, width, height, texture);
		sprite.setPosition(position);

		std::cout << "GameObject created at (" << position.x << ", " << position.y << ")" << std::endl;
	}

	void GameObject::Draw(sf::RenderWindow& window)
	{
		DrawSprite(sprite, window);
	}

	void GameObject::restart()
	{
		sprite.setPosition(startPosition);
	}

}