#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

namespace ArkanoidGame
{
	class Ball;

	class Block : public GameObject
	{
	public:
		void Init() override;
		void Update(float timeDelta) override {}

		bool CheckCollisionWithBall(const Ball& ball) const;
	};
}