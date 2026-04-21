#pragma once
#include "GameObject.h"
#include "Collidable.h"
#include <functional>

namespace ArkanoidGame
{
	class Bonus : public GameObject, public Collidable
	{
	public:
		Bonus(const sf::Vector2f& position);
		virtual ~Bonus() = default;

		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
		bool GetCollision(std::shared_ptr<Collidable> collidableObject) const override;
		void OnHit() override;

		virtual void Activate() = 0;
		bool IsDestroyed() const { return destroyed; }
		void MarkAsDestroyed() { destroyed = true; }

	protected:
		float fallSpeed = 150.f;
		bool destroyed = false;
	};
}
