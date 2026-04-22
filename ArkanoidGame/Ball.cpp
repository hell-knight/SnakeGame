#include "Ball.h"
#include "GameSettings.h"
#include "Sprite.h"
#include "assert.h"
#include "randomizer.h"

namespace
{
	// id textures

	const std::string TEXTURE_ID = "Ball";
}

namespace ArkanoidGame
{
	Ball::Ball(const sf::Vector2f& position)
		: GameObject(SETTINGS.TEXTURES_PATH + TEXTURE_ID + ".png", position, (float)SETTINGS.BALL_SIZE, (float)SETTINGS.BALL_SIZE)
		, behavior(std::make_shared<DefaultBallBehavior>())
	{
		const float angle = 90.f;
		const auto pi = std::acos(-1.f);
		direction.x = std::cos(pi / 180.f * angle);
		direction.y = std::sin(pi / 180.f * angle);
		behavior->OnActivate(this);
	}

	void Ball::Update(float timeDelta)
	{
		if (behavior)
		{
			behavior->Update(this, timeDelta);
		}
	}

	void Ball::InvertDirectionX()
	{
		direction.x *= -1;
	}

	void Ball::InvertDirectionY()
	{
		direction.y *= -1;
	}

	bool Ball::GetCollision(std::shared_ptr<Collidable> collidableObject) const
	{
		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
		assert(gameObject);
		return GetRect().intersects(gameObject->GetRect());
	}

	void Ball::ChangeAngle(float angle)
	{
		lastAngle = angle;
		const auto pi = std::acos(-1.f);
		direction.x = (angle / abs(angle)) * std::cos(pi / 180.f * angle);
		direction.y = -1 * abs(std::sin(pi / 180.f * angle));
	}

	void Ball::restart()
	{
		GameObject::restart();
		const float angle = 90.f;
		const auto pi = std::acos(-1.f);
		direction.x = std::cos(pi / 180.f * angle);
		direction.y = std::sin(pi / 180.f * angle);

		SetBehavior(std::make_shared<DefaultBallBehavior>());
	}

	void Ball::OnHit()
	{
		lastAngle += random<float>(-5, 5);
		ChangeAngle(lastAngle);
	}

	void Ball::SetBehavior(std::shared_ptr<IBallBehavior> newBehavior)
	{
		if (newBehavior == nullptr) return;

		if (behavior != nullptr)
			behavior->OnDeactivate(this);

		behavior = newBehavior;
		behavior->OnActivate(this);
	}

}