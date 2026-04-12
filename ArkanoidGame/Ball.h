#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Collidable.h"

namespace ArkanoidGame
{
	class Ball : public GameObject, public Collidable
	{
	public:
		Ball(const sf::Vector2f& position);
		~Ball() = default;

		void Update(float timeDelta) override;

		void InvertDirectionX();
		void InvertDirectionY();

		bool GetCollision(std::shared_ptr<Collidable> collidableObject) const override;
		void ChangeAngle(float angle);

	private:
		void OnHit();
		sf::Vector2f direction;
		float lastAngle = 90;
	};
}