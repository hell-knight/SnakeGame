#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Collidable.h"
#include "IObserver.h"

namespace ArkanoidGame
{
	class Ball : public GameObject, public Collidable, public IObservable
	{
	public:
		Ball(const sf::Vector2f& position);
		~Ball() = default;

		void Update(float timeDelta) override;

		void InvertDirectionX();
		void InvertDirectionY();

		bool GetCollision(std::shared_ptr<Collidable> collidableObject) const override;
		void ChangeAngle(float angle);
		void restart() override;

		// Geter for decorator
		const sf::Vector2f& GetDirection() const { return direction; }
		float GetLastAngle() const { return lastAngle; }

		// State restoration setters
		void SetDirection(const sf::Vector2f& dir) { direction = dir; }
		void SetLastAngle(float angle) { lastAngle = angle; }
		void SetPosition(const sf::Vector2f& pos) { sprite.setPosition(pos); }


	/*protected:
		sf::Vector2f direction;
		float lastAngle = 90;*/


	private:
		void OnHit();
		sf::Vector2f direction;
		float lastAngle = 90;
	};
}