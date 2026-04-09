#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

namespace ArkanoidGame
{
	class Platform;
	class Block;

	class Ball : public GameObject
	{
	public:
		void Init() override;
		void Update(float timeDelta) override;

		void ReboundFromPlatform();
		void ReboundFromBlock(const Block& block);

	private:
		sf::Vector2f direction;
	};
}