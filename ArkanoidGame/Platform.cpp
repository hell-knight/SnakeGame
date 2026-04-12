#include "Platform.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <algorithm>
#include "Ball.h"

namespace
{
	const std::string TEXTURE_ID = "Platform";
}

namespace ArkanoidGame
{
	Platform::Platform(const sf::Vector2f& position)
		: GameObject(TEXTURES_PATH + TEXTURE_ID + ".png", position, PLATFORM_WIDTH, PLATFORM_HEIGHT)
	{
	}

	void Platform::Update(float timeDelta)
	{
		float moveX = 0.f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			Move(-timeDelta * PLATFORM_SPEED);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Move(timeDelta * PLATFORM_SPEED);
		}
	}

	bool Platform::GetCollision(std::shared_ptr<Collidable> collidable) const
	{
		auto ball = std::static_pointer_cast<Ball>(collidable);
		if (!ball) return false;

		auto sqr = [](float x) {
			return x * x;
		};

		const auto rect = sprite.getGlobalBounds();
		const auto ballPos = ball->GetPosition();
		if (ballPos.x < rect.left)
		{
			return sqr(ballPos.x - rect.left) + sqr(ballPos.y - rect.top) < sqr(BALL_SIZE / 2.0);
		}

		if (ballPos.x > rect.left + rect.width)
		{
			return sqr(ballPos.x - rect.left - rect.width) + sqr(ballPos.y - rect.top) < sqr(BALL_SIZE / 2.0);
		}

		return std::fabs(ballPos.y - rect.top) <= BALL_SIZE / 2.0;
	}

	bool Platform::CheckCollision(std::shared_ptr<Collidable> collidable)
	{
		auto ball = std::static_pointer_cast<Ball>(collidable);
		if (!ball) return false;

		if (GetCollision(ball))
		{
			auto rect = GetRect();
			auto ballPosInPlatform = (ball->GetPosition().x - (rect.left + rect.width / 2.f)) / (rect.width / 2.f);
			ball->ChangeAngle(90.f - 20.f * ballPosInPlatform);
			return true;
		}
		return false;
	}

	void Platform::Move(float speed)
	{
		auto position = sprite.getPosition();
		position.x = std::clamp(position.x + speed, PLATFORM_WIDTH / 2.f , SCREEN_WIDTH - PLATFORM_WIDTH / 2.f);
		sprite.setPosition(position);
	}
}