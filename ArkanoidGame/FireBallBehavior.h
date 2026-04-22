#pragma once
#include <memory>

namespace ArkanoidGame
{
    class Ball;
    class Block;
    class Platform;

    class IBallBehavior
    {
    public:
        virtual ~IBallBehavior() = default;

        // Ball Movement Update
        virtual void Update(Ball* ball, float timeDelta) = 0;

        // Handles a collision with a block. Returns true if the direction has changed.
        virtual bool HandleBlockCollision(Ball* ball, std::shared_ptr<Block> block) = 0;

        // Handling a collision with the platform
        virtual void HandlePlatformCollision(Ball* ball, Platform* platform) = 0;

        // Speed multiplier
        virtual float GetSpeedMultiplier() const = 0;

        // Identification of the active fireball
        virtual bool IsFireball() const { return false; }

        virtual void OnActivate(Ball* ball) {};
        virtual void OnDeactivate(Ball* ball) {};
    };

    class DefaultBallBehavior : public IBallBehavior
    {
        void Update(Ball* ball, float timeDelta) override;
        bool HandleBlockCollision(Ball* ball, std::shared_ptr<Block> block) override;
        void HandlePlatformCollision(Ball* ball, Platform* platform) override;
        float GetSpeedMultiplier() const override { return 1.0f; }

        void OnActivate(Ball* ball) override;
    };

    class FireballBehavior : public IBallBehavior
    {
    public:
        void Update(Ball* ball, float timeDelta) override;
        bool HandleBlockCollision(Ball* ball, std::shared_ptr<Block> block) override;
        void HandlePlatformCollision(Ball* ball, Platform* platform) override;
        float GetSpeedMultiplier() const override { return 1.5f; }
        bool IsFireball() const { return true; }

        void OnActivate(Ball* ball) override;
        void OnDeactivate(Ball* ball) override;
    };
}