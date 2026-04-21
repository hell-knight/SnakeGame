#pragma once
#include "GameObject.h"
#include "Ball.h"
#include "Collidable.h"
#include "IDelayedAction.h"
#include "IObserver.h"

namespace ArkanoidGame
{
	class Block : public GameObject, public Collidable, public IObservable
	{
	protected:
		void OnHit();
		int hitCount = 1;
	public:
		Block(const sf::Vector2f& position, const sf::Color& color = sf::Color::Green);
		virtual ~Block();
		bool GetCollision(std::shared_ptr<Collidable> collidableObject) const override;
		void Update(float timeDelta) override;
		bool IsBroken();
		virtual bool AffectsBallDirection() const { return true; }

		virtual int GetPoints() const = 0;

		virtual void TakeDamage(int damage = 1);
	};

	class SmoothDestroyableBlock : public Block, public IDelayedAction
	{
	protected:
		void OnHit() override;
		sf::Color color;
	public:
		SmoothDestroyableBlock(const sf::Vector2f& position, const sf::Color& color = sf::Color::Green);
		~SmoothDestroyableBlock() = default;
		void Update(float timeDelta) override;

		bool GetCollision(std::shared_ptr<Collidable> collidableObject) const override;
		void FinalAction() override;
		void EachTickAction(float deltaTime) override;

		int GetPoints() const override { return 20; }

		void TakeDamage(int damage = 1) override;
	};

	class UnbreackableBlock : public Block
	{
	public:
		UnbreackableBlock(const sf::Vector2f& position);
		void OnHit() override;
		void Update(float)
		{
			int i = 0;
			++i;
		}
		int GetPoints() const override { return 0; }

		void TakeDamage(int damage = 1) override;
	};
}