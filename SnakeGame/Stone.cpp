#include "Stone.h"
#include "Constants.h"

namespace SnakeGame
{
	void InitStone(Stone& stone, const sf::Texture& texture)
	{
		// init stone sprite
		stone.sprite.setTexture(texture);
		SetSpriteSize(stone.sprite, CELL_SIZE, CELL_SIZE);
		SetSpriteRelativeOrigin(stone.sprite, 0.5f, 0.5f);
	}

	void DrawStone(Stone& stone, sf::RenderWindow& window, float topPanelHeight)
	{
		stone.sprite.setPosition(float(stone.position.x * CELL_SIZE + CELL_SIZE / 2),
			float(stone.position.y * CELL_SIZE + CELL_SIZE / 2 + topPanelHeight));
		window.draw(stone.sprite);
	}


}