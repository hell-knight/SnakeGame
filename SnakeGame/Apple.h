#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace SnakeGame
{
	enum class AppleType
	{
		Normal = 0,
		Big,			// big — lots of points, but it disappears after a while
		Poisoned,		// Poisoned — speeds up the snake (temporarily)
		Disorienting	// disorienting — reverses control (temporarily)
	};

	struct Apple
	{
		Position2I position;
		sf::Sprite sprite;
		AppleType type = AppleType::Normal;
		float lifetime = 0.f;
		int points = 10;
		bool isAppleEaten = false;
	};
	
	void InitApples(Apple& apple, const sf::Texture& texture);
	void DrawApple(Apple& apple, sf::RenderWindow& window, float topPanelHeight);
}