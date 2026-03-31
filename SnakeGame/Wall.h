#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace SnakeGame
{

	struct Wall
	{
		sf::RectangleShape wallShape;
	};

	struct Game;

	void InitWall(std::vector<Wall>& wall, float topPanelHeight);
	void DrawWall(std::vector<Wall>& wall, sf::RenderWindow& window);
}