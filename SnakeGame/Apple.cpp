#include "Apple.h"
#include "Game.h"

namespace SnakeGame
{
	void InitApples(Apple& apple, const sf::Texture& texture)
	{
		// init apple sprite
		apple.sprite.setTexture(texture);
		SetSpriteSize(apple.sprite, CELL_SIZE, CELL_SIZE);
		SetSpriteRelativeOrigin(apple.sprite, 0.5f, 0.5f);

	}
	
	void DrawApple(Apple& apple, sf::RenderWindow& window, float topPanelHeight)
	{
		if (apple.type == AppleType::Big)
		{
			SetSpriteSize(apple.sprite, 2 * CELL_SIZE, 2 * CELL_SIZE);
		}
		else
		{
			SetSpriteSize(apple.sprite, CELL_SIZE, CELL_SIZE);
		}
		apple.sprite.setPosition( float(apple.position.x * CELL_SIZE + CELL_SIZE / 2),
			float(apple.position.y * CELL_SIZE + CELL_SIZE / 2 + topPanelHeight) );
		window.draw(apple.sprite);
	}
}