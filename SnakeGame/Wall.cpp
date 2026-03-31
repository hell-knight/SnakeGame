#include "Wall.h"
#include "Game.h"

namespace SnakeGame
{
	void InitWall(std::vector<Wall>& wall, float topPanelHeight)
	{
		wall.clear();
		wall.resize(GRID_SIZE * 4 - 4);

		int index = 0;
		// top wall
		for (int x = 0; x < GRID_SIZE; ++x)
		{
			wall[index].wallShape.setSize({ CELL_SIZE, CELL_SIZE });
			wall[index].wallShape.setPosition(static_cast<float>(x * CELL_SIZE), static_cast<float>(0 + topPanelHeight));
			index++;
		}

		// bottom wall
		for (int x = 0; x < GRID_SIZE; ++x)
		{
			wall[index].wallShape.setSize({ CELL_SIZE, CELL_SIZE });
			wall[index].wallShape.setPosition(static_cast<float>(x * CELL_SIZE), static_cast<float>((GRID_SIZE - 1) * CELL_SIZE + topPanelHeight));
			index++;
		}

		// left wall without corners
		for (int y = 1; y < GRID_SIZE - 1; ++y)
		{
			wall[index].wallShape.setSize({ CELL_SIZE, CELL_SIZE });
			wall[index].wallShape.setPosition(0, y * CELL_SIZE + topPanelHeight);
			index++;
		}

		// right wall without corners
		for (int y = 1; y < GRID_SIZE - 1; ++y)
		{
			wall[index].wallShape.setSize({ CELL_SIZE, CELL_SIZE });
			wall[index].wallShape.setPosition((GRID_SIZE - 1) * CELL_SIZE, y * CELL_SIZE + topPanelHeight);
			index++;
		}

		for (auto& stone : wall)
		{
			stone.wallShape.setFillColor(sf::Color::Green);
			stone.wallShape.setOutlineThickness(2.f);
			stone.wallShape.setOutlineColor(sf::Color(40, 40, 40));
		}
	}

	void DrawWall(std::vector<Wall>& wall, sf::RenderWindow& window)
	{
		
		for (auto& seg : wall)
		{
			window.draw(seg.wallShape);
		}
	}
}