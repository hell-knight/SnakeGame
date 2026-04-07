#pragma once
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
	class Platform;

	class Ball
	{
	public:
		void Init();
		void Update(float timeDelta, const Platform& platform);
		void Draw(sf::RenderWindow& window) const;

		sf::FloatRect GetBounds() const;

	private:
		void BounceX();
		void BounceY();

		sf::Sprite sprite;
		sf::Texture texture;
		sf::Vector2f velocity;
	};
}