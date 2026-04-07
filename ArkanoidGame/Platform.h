#pragma once
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
	class Platform
	{
	public:
		void Init();
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window) const;

		sf::FloatRect GetBounds() const;

	private:
		sf::Sprite sprite;
		sf::Texture texture;
		float speed = 500.f;
	};
}