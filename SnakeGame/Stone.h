#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace SnakeGame
{
	struct Stone
	{
		Position2I position;
		sf::Sprite sprite;

		float lifetime = 0.f;
	};

	void InitStone(Stone& stone, const sf::Texture& texture);
	void DrawStone(Stone& stone, sf::RenderWindow& window, float topPanelHeight);
}