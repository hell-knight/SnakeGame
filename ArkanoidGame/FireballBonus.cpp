#include "FireballBonus.h"
#include "BonusManager.h"
#include "Block.h"
#include "Platform.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <cassert>
#include <cmath>
#include <iostream>

namespace ArkanoidGame
{
	FireballBonus::FireballBonus(const sf::Vector2f& position)
		: Bonus(position)
	{
		sprite.setColor(sf::Color::Magenta);
		SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
	}

	void FireballBonus::Activate()
	{
		BONUS_MANAGER.ActivateBonus(BonusType::Fireball, 7.0f);
	}

	void FireballBonus::Update(float timeDelta)
	{
		Bonus::Update(timeDelta);

		// Add a rotation animation
		sprite.rotate(180.0f * timeDelta);
	}

	// FireballDecorator implementation
	FireballDecorator::FireballDecorator(std::shared_ptr<Ball> wrapped)
		: Ball(wrapped->GetPosition())
		, wrappedBall(wrapped)
	{
		std::cout << "FireballDecorator created at (" << GetPosition().x << ", " << GetPosition().y << ")" << std::endl;
		assert(wrappedBall != nullptr);

		// Set up the sprite with the new texture
		/*sprite.setPosition(wrapped->GetPosition());
		SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);*/
		
		SetDirection(wrapped->GetDirection());
		SetLastAngle(wrapped->GetLastAngle());
		SetPosition(wrapped->GetPosition());
		sprite.setColor(sf::Color::Red);
	}

	void FireballDecorator::Update(float timeDelta)
	{
		if (!wrappedBall) return;

		// Updating the wrapped ball at an increased speed
		wrappedBall->Update(timeDelta * speedMultiplier);

		// Synchronize the position
		//sprite.setPosition(wrappedBall->GetPosition());
		SetPosition(wrappedBall->GetPosition());
		SetDirection(wrappedBall->GetDirection());
		SetLastAngle(wrappedBall->GetLastAngle());
	}

	void FireballDecorator::Draw(sf::RenderWindow& window)
	{
		/*if (!wrappedBall) return;

		wrappedBall->Draw(window);*/
		window.draw(sprite);
	}

	void FireballDecorator::restart()
	{
		Ball::restart();
		if (wrappedBall)
		{
			wrappedBall->restart();
			SetPosition(wrappedBall->GetPosition());
			//sprite.setPosition(wrappedBall->GetPosition());
			SetDirection(wrappedBall->GetDirection());
			SetLastAngle(wrappedBall->GetLastAngle());
		}
	}

	/*const sf::Vector2f& FireballDecorator::GetPosition() const
	{
		if (wrappedBall)
		{
			return wrappedBall->GetPosition();
		}
		return GameObject::GetPosition();
	}*/

	/*sf::FloatRect FireballDecorator::GetRect() const
	{
		if (wrappedBall)
		{
			return wrappedBall->GetRect();
		}
		return GameObject::GetRect();
	}*/

	bool FireballDecorator::GetCollision(std::shared_ptr<Collidable> collidableObject) const
	{
		/*auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
		if (!gameObject) return false;

		sf::FloatRect myRect = sprite.getGlobalBounds();
		sf::FloatRect otherRect = gameObject->GetRect();

		std::cout << "Fireball rect: (" << myRect.left << ", " << myRect.top
			<< ", " << myRect.width << ", " << myRect.height << ")" << std::endl;
		std::cout << "Other rect: (" << otherRect.left << ", " << otherRect.top
			<< ", " << otherRect.width << ", " << otherRect.height << ")" << std::endl;

		bool intersects = myRect.intersects(otherRect);
		std::cout << "Intersects: " << (intersects ? "YES" : "NO") << std::endl;

		return intersects;*/
		//return Ball::GetCollision(collidableObject);

		if (!wrappedBall) return false;
		return wrappedBall->GetCollision(collidableObject);
	}

	bool FireballDecorator::CheckCollision(std::shared_ptr<Collidable> collidable)
	{
		//std::cout << "FireballDecorator::CheckCollision called" << std::endl;

		//// Проверяем коллизию
		//bool hasCollision = GetCollision(collidable);
		//std::cout << "  GetCollision result: " << (hasCollision ? "TRUE" : "FALSE") << std::endl;


		//// Check collision
		//if (!GetCollision(collidable))
		//{
		//	return false;
		//}

		if (!wrappedBall) return false;
		/*if (!wrappedBall->GetCollision(collidable))
		{
			return false;
		}*/

		// Determine the object type
		auto block = std::dynamic_pointer_cast<Block>(collidable);
		//auto platform = std::dynamic_pointer_cast<Platform>(collidable);

		if (block)
		{
			// For a block: deal damage via TakeDamage (if the method is implemented)
			// or via a public method
			block->TakeDamage(999);

			return true;
		}
		//else if (platform)
		//{
		//	std::cout << "FireBall with PLATFORM" << std::endl;
		//	/*bool collided = wrappedBall->CheckCollision(collidable);
		//	if (collided)
		//	{
		//		sprite.setPosition(wrappedBall->GetPosition());
		//		Emit();
		//	}
		//	return collided;*/
		//	/*auto self = std::dynamic_pointer_cast<Ball>(shared_from_this());
		//	return platform->CheckCollision(self);*/
		//	sf::FloatRect platformRect = platform->GetRect();
		//	sf::Vector2f ballPos = sprite.getPosition();

		//	// Вычисляем относительную позицию на платформе
		//	float relativePos = (ballPos.x - (platformRect.left + platformRect.width / 2.0f)) / (platformRect.width / 2.0f);
		//	relativePos = std::clamp(relativePos, -1.0f, 1.0f);

		//	float angle = 90.0f - 30.0f * relativePos;

		//	std::cout << "  relativePos: " << relativePos << ", angle: " << angle << std::endl;

		//	// Меняем угол
		//	ChangeAngle(angle);

		//	// Отталкиваем мяч от платформы
		//	ballPos.y = platformRect.top - SETTINGS.BALL_SIZE / 2.0f - 1.0f;
		//	sprite.setPosition(ballPos);

		//	// Синхронизируем с wrappedBall
		//	if (wrappedBall)
		//	{
		//		wrappedBall->SetPosition(ballPos);
		//		wrappedBall->ChangeAngle(angle);
		//	}

		//	return true;
		//}
		//else
		//{
		//	bool result = wrappedBall->CheckCollision(collidable);

		//	// Синхронизируем состояние после коллизии
		//	if (result)
		//	{
		//		//sprite.setPosition(wrappedBall->GetPosition());
		//		SetPosition(wrappedBall->GetPosition());
		//		SetDirection(wrappedBall->GetDirection());
		//		SetLastAngle(wrappedBall->GetLastAngle());
		//	}

		//	return result;
			/*sf::Vector2f ballPos = sprite.getPosition();

			if (ballPos.x - SETTINGS.BALL_SIZE / 2.0f <= 0 ||
				ballPos.x + SETTINGS.BALL_SIZE / 2.0f >= SETTINGS.SCREEN_WIDTH)
			{
				InvertDirectionX();
			}
			if (ballPos.y - SETTINGS.BALL_SIZE / 2.0f <= 0)
			{
				InvertDirectionY();
			}

			return true;*/

			//return Ball::CheckCollision(collidable);
		//}
		else
		{
			std::cout << "Fireball hit PLATFORM or WALL!" << std::endl;
			// Делегируем wrappedBall обработку столкновения
			bool result = wrappedBall->CheckCollision(collidable);

			// Синхронизируем состояние после коллизии
			if (result)
			{
				sprite.setPosition(wrappedBall->GetPosition());
				SetDirection(wrappedBall->GetDirection());
				SetLastAngle(wrappedBall->GetLastAngle());
			}
			return result;
		}
		//return wrappedBall->CheckCollision(collidable);
	}

	void FireballDecorator::OnHit()
	{
		//Emit();
	}

	void FireballDecorator::InvertDirectionX()
	{
		if (wrappedBall)
		{
			wrappedBall->InvertDirectionX();
		}

		/*sf::Vector2f dir = GetDirection();
		dir.x *= -1;
		SetDirection(dir);
		if (wrappedBall) wrappedBall->SetDirection(dir);*/
	}

	void FireballDecorator::InvertDirectionY()
	{
		if (wrappedBall)
		{
			wrappedBall->InvertDirectionY();
		}

		/*sf::Vector2f dir = GetDirection();
		dir.y *= -1;
		SetDirection(dir);
		if (wrappedBall) wrappedBall->SetDirection(dir);*/
	}

	void FireballDecorator::ChangeAngle(float angle)
	{
		/*if (wrappedBall)
		{
			wrappedBall->ChangeAngle(angle);
		}*/

		Ball::ChangeAngle(angle);
		if (wrappedBall) wrappedBall->ChangeAngle(angle);
	}

	
	const sf::Vector2f& FireballDecorator::GetPosition() const
	{
		if (wrappedBall) return wrappedBall->GetPosition();
		return Ball::GetPosition();
	}

	sf::FloatRect FireballDecorator::GetRect() const
	{
		if (wrappedBall) return wrappedBall->GetRect();
		return Ball::GetRect();
	}


}