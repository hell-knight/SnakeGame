#include "Platform.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <algorithm>
#include "Ball.h"
#include "BonusManager.h"
#include <cmath>
#include <iostream>

namespace
{
	const std::string TEXTURE_ID = "Platform";
}

namespace ArkanoidGame
{
	void DefaultPlatformBehavior::Update(Platform* platform, float timeDelta)
	{
		float moveX = 0.0f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			moveX = -timeDelta * SETTINGS.PLATFORM_SPEED;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			moveX = timeDelta * SETTINGS.PLATFORM_SPEED;
		}

		if (moveX != 0.0f)
		{
			platform->Move(moveX);
		}
	}

	float DefaultPlatformBehavior::CalculateReflectionAngle(float ballPosX, float platformPosX, float platformWidth) const
	{
		float relativePos = (ballPosX - platformPosX) / (platformWidth / 2.0f);
		return 90.0f - 30.0f * relativePos;
	}

	void BonusPlatformBehavior::Update(Platform* platform, float timeDelta)
	{
		float moveX = 0.0f;
		float speed = SETTINGS.PLATFORM_SPEED * GetSpeedMultiplier();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			moveX = -timeDelta * speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			moveX = timeDelta * speed;
		}

		if (moveX != 0.0f)
		{
			platform->Move(moveX);
		}
	}

	float BonusPlatformBehavior::CalculateReflectionAngle(float ballPosX, float platformPosX, float platformWidth) const
	{
		float relativePos = (ballPosX - platformPosX) / (platformWidth / 2.0f);
		return 90.0f - 45.0f * relativePos;
	}


	Platform::Platform(const sf::Vector2f& position)
		: GameObject(SETTINGS.TEXTURES_PATH + TEXTURE_ID + ".png", position, (float)SETTINGS.PLATFORM_WIDTH, (float)SETTINGS.PLATFORM_HEIGHT)
	{
		behavior = std::make_shared<DefaultPlatformBehavior>();

		//sf::FloatRect bounds = sprite.getLocalBounds();
		/*originalTextureWidth = bounds.width;
		originalTextureHeight = bounds.height;*/
	}

	void Platform::Update(float timeDelta)
	{
		// Choosing a strategy based on active bonuses
		if (BONUS_MANAGER.IsPlatformBonusActive())
		{
			if (dynamic_cast<BonusPlatformBehavior*>(behavior.get()) == nullptr)
			{
				SetBehavior(std::make_shared<BonusPlatformBehavior>());
			}
		}
		else
		{
			if (dynamic_cast<DefaultPlatformBehavior*>(behavior.get()) == nullptr)
			{
				SetBehavior(std::make_shared<DefaultPlatformBehavior>());
			}
		}

		// delegating the update of the current strategy
		behavior->Update(this, timeDelta);
	}

	bool Platform::GetCollision(std::shared_ptr<Collidable> collidable) const
	{
		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidable);
		if (!gameObject) return false;

		auto rect = sprite.getGlobalBounds();
		auto objRect = gameObject->GetRect();
		auto objPos = gameObject->GetPosition();

		//auto ball = std::static_pointer_cast<Ball>(collidable);
		auto ball = std::dynamic_pointer_cast<Ball>(collidable);
		//std::cout << "Platform::GetCollision - ball cast: " << (ball ? "SUCCESS" : "FAILED") << std::endl;

		//if (!ball) return false;

		if (ball)
		{
			auto sqr = [](float x) {
				return x * x;
				};

			const auto rect = sprite.getGlobalBounds();
			const auto ballPos = ball->GetPosition();
			if (ballPos.x < rect.left)
			{
				return sqr(ballPos.x - rect.left) + sqr(ballPos.y - rect.top) < sqr((float)SETTINGS.BALL_SIZE / 2.0f);
			}

			if (ballPos.x > rect.left + rect.width)
			{
				return sqr(ballPos.x - rect.left - rect.width) + sqr(ballPos.y - rect.top) < sqr((float)SETTINGS.BALL_SIZE / 2.0f);
			}

			return std::fabs(ballPos.y - rect.top) <= SETTINGS.BALL_SIZE / 2.0;
		}

		return rect.intersects(objRect);
	}

	bool Platform::CheckCollision(std::shared_ptr<Collidable> collidable)
	{
		//auto ball = std::static_pointer_cast<Ball>(collidable);
		auto ball = std::dynamic_pointer_cast<Ball>(collidable);
		if (!ball) return false;

		if (GetCollision(ball))
		{
			auto rect = GetRect();
			/*auto ballPosInPlatform = (ball->GetPosition().x - (rect.left + rect.width / 2.f)) / (rect.width / 2.f);
			ball->ChangeAngle(90.f - 20.f * ballPosInPlatform);*/

			// === fireball ===
			/*sf::Vector2f ballPos = ball->GetPosition();
			ballPos.y = rect.top - SETTINGS.BALL_SIZE / 2.0f - 1.0f;
			ball->SetPosition(ballPos);*/

			float angle = behavior->CalculateReflectionAngle(
				ball->GetPosition().x,
				rect.left + rect.width / 2.0f,
				rect.width
			);
			ball->ChangeAngle(angle);
			return true;
		}
		return false;
	}

	void Platform::restart()
	{
		sprite.setPosition({ SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT - SETTINGS.PLATFORM_HEIGHT / 2.f });
	}

	void Platform::SetBehavior(std::shared_ptr<IPlatformBehavior> newBehavior)
	{
		if (newBehavior)
		{
			behavior = newBehavior;
			float widthMultiplier = behavior->GetWidthMultiplier();

			SetSpriteSize(sprite, SETTINGS.PLATFORM_WIDTH * widthMultiplier, SETTINGS.PLATFORM_HEIGHT);
			//SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
		}
	}

	float Platform::GetCurrentWidth() const
	{
		//std::cout << "behavior->GetWidthMultiplier(): " << behavior->GetWidthMultiplier() << std::endl;
		//return SETTINGS.PLATFORM_WIDTH * behavior->GetWidthMultiplier();
		return sprite.getGlobalBounds().width;
	}

	void Platform::Move(float speed)
	{
		auto position = sprite.getPosition();

		float currentWidth = GetCurrentWidth();
		//std::cout << "currentWidth: " << currentWidth << std::endl;
		position.x = std::clamp(position.x + speed,
			currentWidth / 2.0f,
			SETTINGS.SCREEN_WIDTH - currentWidth / 2.0f);

		sprite.setPosition(position);
	}
}